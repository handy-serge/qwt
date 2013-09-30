package org.flowcyt.cfcs;
// CFCSDataSet.java

/* ------------------------------------------------------------------------- *\
 This software and documentation are provided 'as is' and Tree Star, Inc., its
 contractors and partners specifically disclaim all other warranties, expressed
 or implied, including but not limited to implied warranties of merchantability
 and fitness for a particular purpose, or during any particular date range.

 By using this software, you are agreeing to these limits of liability, and to
 hold Tree Star harmless for any information, accurate or erroneous, that might
 be generated by the program.  This software is intended for research use only.

 Christopher Lane <cdl@best.classes> for Tree Star  1/21/2002      Copyright 2002
 \* ------------------------------------------------------------------------- */

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

public final class CFCSDataSet implements CFCSErrorCodes
{
    public static final int UNDEFINED = -1;
    public static final int HEADER = 0;
    public static final int TEXT = 1;
    public static final int DATA = 2;
    public static final int ANALYSIS = 3;
    public static final int OTHER_START = 4;

    private static final int VERSION_FIELD_SIZE = 10;
    private static final int OFFSET_FIELD_SIZE = 8;
    private static final int CHECKSUM_FIELD_SIZE = 8;

    private static final int BLOCK_SIZE = 256;
    private static final int HEADER_OFFSET_LIMIT = 99999999;
    private static final String DISABLED_CHECKSUM = "00000000";
    private static final int CHECKSUM_DISABLED = -1;

    private static final String VERSION_PREFIX = "FCS";

    private static final int SEGMENT = 0, BEGIN = 1, END = 2;

    private final static String DEFAULT_VERSION = "FCS3.0";
    private final static String HEADER_RESERVED = "    ";
    /* friendly */
    final static int DEFAULT_DATATYPE = CFCSDatatype.BINARY;

    private CFCSData data;
    private String version = DEFAULT_VERSION;
    private final CFCSKeywords keywords = new CFCSKeywords();
    private final List<Object> segments = new ArrayList<Object>(OTHER_START);
    
    private int crc16 = 0;
    private boolean bReadSegmentsFirstTime = true;

    // --------------------------------------------------------------------

    /* friendly */
    CFCSDataSet()
    {
        for (int i = HEADER; i < OTHER_START; i++)
            segments.add(null);
    }

    // --------------------------------------------------------------------

    /* friendly */
    CFCSDataSet(final CFCSSystem.SentientInputStream stream)
    {
        this();

        final List<long[]> headers = new LinkedList<long[]>();

        try
        {
            version = readFileVersion(stream);

            if (getVersionIntegerValue() < 2)
            { // Need spec for FCS1.0
                throw new CFCSError(CFCSVersionNotSupported, version);
            }

            long first = Long.MAX_VALUE; // Help us find where header segment ends

            for (int i = TEXT; i < OTHER_START; i++)
            {
                long begin = readOffset(stream);
                long end = readOffset(stream);

                long[] header = { i, begin, end };
                headers.add(header);

                if (begin > 0L && begin < first)
                    first = begin;
            }

            for (int i = OTHER_START;; i++)
            { // Private segments
            	
                // JS, there was a bug... if (first >= stream.getFilePointer()) break;
            	if (stream.getFilePointer() + 2 * OFFSET_FIELD_SIZE > first)
                    break; // JS: There cannot be more headers because the first segment is going to start  

                long begin, end;

                // JS:
                // Cannot just finish reading, sometimes there are a few 0,0 headers and then there is
                // a valid one.
                /*
                if ((begin = readOffset(stream)) == 0L)	
                    break;
                if ((end = readOffset(stream)) == 0L)
                    break;
                */
                
                // JS, new code, only skiping the 0,0 segments.
                begin = readOffset(stream);
                end = readOffset(stream);
                if((begin == 0L) || (end == 0L)) continue;

                long[] header = { i, begin, end };
                headers.add(header);
                segments.add(null);

                if (begin > 0L && begin < first)
                    first = begin;
            }

            readSegments(headers, stream);

            addKeywords(TEXT);

            if (getVersionIntegerValue() >= 3)
            { // Process the oversize (> 100MB) segments
                headers.clear();

                segments.set(TEXT, null); // Clear space for STEXT

                for (int i = TEXT; i < OTHER_START; i++)
                { // Well-known segments
                    CFCSKeyword keyword = keywords.getKeyword(CFCSKeywords.SEGMENT_BEGIN_PREFIX + CFCSKeywords.SEGMENT_ROOTS[i]);
                    long begin = keyword.getKeywordLongValue();

                    keyword = keywords.getKeyword(CFCSKeywords.SEGMENT_END_PREFIX + CFCSKeywords.SEGMENT_ROOTS[i]);
                    long end = keyword.getKeywordLongValue();

                    long[] header = { i, begin, end };

                    headers.add(header);
                }

                readSegments(headers, stream);

                if (segments.get(TEXT) != null)
                    addKeywords(TEXT); // STEXT
                
                // JS
                crc16 = stream.getCRC16();	// Must be saved before reading CRC from file (which changes the saved one)
                int checksum = readFileChecksum(stream);

                // JS: uncomment this to see CRC comparisons
                // if (checksum == CHECKSUM_DISABLED) System.out.println("CRCs: Computed CRC: " + crc16 + ", file says: disabled (\"00000000\")");
                // else System.out.println("CRCs: Computed CRC: " + crc16 + ", file says: " + checksum);
                
                if ((checksum != CHECKSUM_DISABLED) && (checksum != crc16))
                    throw new CFCSError(CFCSBadFCS, "Malformed checksum, read in file: " + checksum + ", computed: " + crc16);
            }

            if (segments.get(ANALYSIS) != null)
                addKeywords(ANALYSIS);

            data = selectMode(selectDatatype());

            byte[] bytes = (byte[]) segments.get(DATA);

            data.setBytes(bytes);
        }
        catch (IOException exception)
        {
            throw new CFCSError(CFCSNetworkIOError, exception);
        }
    }

    // --------------------------------------------------------------------

    /* friendly */
    CFCSDataSet(final CFCSDataSet source)
    {
        this();

        try
        {

            CFCSKeywords sourceKeywords = source.getKeywords();

            for (int i = 0, count = sourceKeywords.getCount(); i < count; i++)
            {
                CFCSKeyword keyword = sourceKeywords.getKeyword(i);

                String name = keyword.getKeywordName();

                if (CFCSKeywords.NONTRANSFERABLE_KEYWORDS.contains(name))
                    continue;

                keywords.addSystemKeyword(keyword);
            }

            for (int i = OTHER_START, count = source.getCount(); i < count; i++)
            { // copy private segments
                CFCSOtherSegment segment = source.getOtherSegment(i);

                segments.add(segment.copy());
            }
        }
        catch (CFCSError exception)
        {
            throw new CFCSError(CFCSBadSourceSet, exception);
        }

        data = selectMode(selectDatatype());
    }

    // --------------------------------------------------------------------

    /* friendly */
    CFCSDataSet(final int mode, final int type)
    {
        this();

        if (keywords.getMode() == CFCSData.UNDEFINED)
            keywords.setMode(mode);
        else
            throw new CFCSError(CFCSInconsistentAttribute, CFCSKeywords.MODE_KEYWORD);

        if (keywords.getDatatype() == CFCSDatatype.UNDEFINED)
            keywords.setDatatype(type);
        else
            throw new CFCSError(CFCSInconsistentAttribute, CFCSKeywords.DATATYPE_KEYWORD);

        (new CFCSParameters(keywords)).setCount(0); // Force $PAR keyword to exist

        data = selectMode(selectDatatype());
    }
    
    public int getDatatype() {
    	return keywords.getDatatype();
    }

    // --------------------------------------------------------------------
    // Glitch: OTHER segments should be between TEXT and DATA, since they
    // are bound by 100MB limit, rather than following ANALYSIS.

    /* friendly */
    final void writeDataSet(final CFCSSystem.SentientOutputStream stream, final long another)
    {

        // Set all unresolved offset keywords to a maximum value for estimation

        for (int i = TEXT; i < OTHER_START; i++)
        {
            String suffix = CFCSKeywords.SEGMENT_ROOTS[i];
            String[] prefixes = { CFCSKeywords.SEGMENT_BEGIN_PREFIX, CFCSKeywords.SEGMENT_END_PREFIX };

            for (int j = 0; j < prefixes.length; j++)
            {
                CFCSKeyword keyword = null;
                String offset = prefixes[j] + suffix;

                try
                {
                    keyword = keywords.getKeyword(offset);
                    keyword.setKeywordLongValue(Long.MAX_VALUE);
                }
                catch (CFCSError exception)
                {
                    keyword = new CFCSKeyword(offset, Long.MAX_VALUE);
                }

                keywords.addSystemKeyword(keyword);
            }
        }

        // Set unresolved $NEXTDATA keyword to a maximum value for estimation

        CFCSKeyword nextdata;

        try
        {
            nextdata = keywords.getKeyword(CFCSKeywords.NEXTDATA_KEYWORD);
            nextdata.setKeywordLongValue(Long.MAX_VALUE);
        }
        catch (CFCSError exception)
        {
            nextdata = new CFCSKeyword(CFCSKeywords.NEXTDATA_KEYWORD, Long.MAX_VALUE);
        }

        keywords.addSystemKeyword(nextdata);

        // Convert the content for all the segments (ready or not) into bytes

        final List<long[]> headers = new LinkedList<long[]>();

        int stext = UNDEFINED;

        byte[] text = null;

        for (int segIdx = HEADER; segIdx < OTHER_START; segIdx++)
        {
            byte[] bytes = null;

            switch (segIdx)
            {
                case HEADER:
                    bytes = generateHeader(headers, stext); // Just an estimate
                    break;
                case TEXT:
                    bytes = text = keywords.getBytes(TEXT); // Just an estimate
                    break;
                case DATA:
                    bytes = data.getBytes();
                    break;
                case ANALYSIS:
                    bytes = keywords.getBytes(ANALYSIS);
                    break;
                default:
                    break; // OTHER segments should already be in proper format
            }

            segments.set(segIdx, bytes);
        }

        // If the TEXT segment will be too large, split up the keywords

        if ((text.length + BLOCK_SIZE) > HEADER_OFFSET_LIMIT)
        {
            byte[] other_keywords = keywords.getTextBytes(false);

            if (other_keywords != null)
            {
                segments.set(TEXT, keywords.getTextBytes(true)); // FCS-defined keywords (estimate)
                segments.add(stext = OTHER_START, other_keywords); // All the other keywords
            }
            else
                throw new CFCSError(CFCSBadFCS); // We've overflowed with just FCS-defined keywords!
        }

        // Calculate offsets for all the segments

        long next = 0L, position = 0L;

        for (int i = HEADER, size = segments.size(); i < size; i++)
        { // all segments
            long begin = 0L, end = 0L;
            byte[] bytes = (byte[]) segments.get(i);

            if (bytes != null)
            {
                long[] header = { i, (begin = position), (end = position + bytes.length - 1) };

                headers.add(header);

                position = roundToBlock(next = end + 1);
            }

            if ((i > HEADER && i < OTHER_START) || i == stext)
            {
                int index = i;

                if (index == TEXT)
                    begin = end = 0L;
                else if (index == stext)
                    index = TEXT;

                CFCSKeyword keyword = keywords.getKeyword(CFCSKeywords.SEGMENT_BEGIN_PREFIX + CFCSKeywords.SEGMENT_ROOTS[index]);
                keyword.setKeywordLongValue(begin);
                keywords.replaceSystemKeyword(keyword);

                keyword = keywords.getKeyword(CFCSKeywords.SEGMENT_END_PREFIX + CFCSKeywords.SEGMENT_ROOTS[index]);
                keyword.setKeywordLongValue(end);
                keywords.replaceSystemKeyword(keyword);
            }
        }

        // Set the $NEXTDATA keyword to point after this dataset, if needed

        if (another > -1L)
        {
            next = roundToBlock(next + CHECKSUM_FIELD_SIZE);
            // nextdata.setKeywordLongValue(another + next);
            // JS bug fix? The index should be based on the beginning of the previous data set, not based on the beginning of the data file
            nextdata.setKeywordLongValue(next);
        }
        else
            nextdata.setKeywordLongValue(0L);
        keywords.replaceSystemKeyword(nextdata);

        // All the keywords and offsets are now ready, regenerate the TEXT and HEADER segments

        segments.set(TEXT, (stext == UNDEFINED) ? keywords.getBytes(TEXT) : keywords.getTextBytes(true));
        long[] header = (long[]) headers.get(TEXT);
        header[END] = header[BEGIN] + ((byte[]) segments.get(TEXT)).length - 1;

        segments.set(HEADER, generateHeader(headers, stext));
        header = (long[]) headers.get(HEADER);
        header[END] = header[BEGIN] + ((byte[]) segments.get(HEADER)).length - 1;

    	// Bug fix by Josef Spidlen, March 5, 2009
        //
        // Files >100MB have 0 offsets in the header, we need to replace these by the correct value
        // that is in the keyword only.
    	for (int i = 0; i < headers.size(); i++)
        {
    		header = (long[]) headers.get(i);
    		if(header[BEGIN] == 0L && header[END] == 0L) {
            	String suffix = CFCSKeywords.SEGMENT_ROOTS[i];
            	String[] prefixes = { CFCSKeywords.SEGMENT_BEGIN_PREFIX, CFCSKeywords.SEGMENT_END_PREFIX };
            	
            	for(int j = 0; j < prefixes.length; j++)
                {
                    CFCSKeyword keyword = null;
                    keyword = keywords.getSystemKeyword(prefixes[j] + suffix);
                    if(keyword != null) header[j+1] = keyword.getKeywordLongValue();
                }
            	headers.set(i, header);
            }
        }
    	// End of code added by JS

        
        
        // Finally write the segments out

        try
        {
            writeSegments(headers, stream);

            writeFileChecksum(stream, DISABLED_CHECKSUM);

            if (another > -1L)
                stream.skip(next - stream.getFilePointer()); // optional but nice
        }
        catch (IOException exception)
        {
            throw new CFCSError(CFCSNetworkIOError, exception);
        }
    }

    // --------------------------------------------------------------------

    private byte[] generateHeader(final List<long[]> headers, final int stext)
    {
        final StringBuffer buffer = new StringBuffer();

        (buffer.append(DEFAULT_VERSION)).append(HEADER_RESERVED);

        final int size = segments.size();

        for (int i = TEXT; i < size; i++)
        {
            if (i == stext)
                continue; // Only appears in TEXT, not HEADER

            long[] header = { i, 0L, 0L };

            if (i < headers.size())
                header = (long[]) headers.get(i);

            if (header[BEGIN] > HEADER_OFFSET_LIMIT || header[END] > HEADER_OFFSET_LIMIT)
            {
                if (i >= OTHER_START)
                    continue; // Can't have OTHER segments beyond 100MB limit
                /* else */header[BEGIN] = header[END] = 0L;
            }

            buffer.append(formatNumber((int) header[BEGIN], OFFSET_FIELD_SIZE, CFCSSystem.PAD_CHAR));
            buffer.append(formatNumber((int) header[END], OFFSET_FIELD_SIZE, CFCSSystem.PAD_CHAR));
        }

        return (buffer.toString()).getBytes();
    }

    // --------------------------------------------------------------------

    private static String formatNumber(final int offset, final int size, final char pad)
    {
        String string = Integer.toString(offset);

        if (string.length() > size)
        {
            throw new CFCSError(CFCSBadFCS);
        }
        /* else */while (string.length() < size)
            string = pad + string;

        return string;
    }

    // --------------------------------------------------------------------

    private static long roundToBlock(final long offset)
    {
        return ((offset / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    }

    // --------------------------------------------------------------------

    private CFCSData selectMode(final CFCSDatatype datatype)
    {
        final int mode = keywords.getMode();

        switch (mode)
        {
            case CFCSData.LISTMODE:
                return new CFCSListModeData(datatype, keywords);
            case CFCSData.CORRELATED:
                return new CFCSCorrelatedData(datatype, keywords);
            case CFCSData.UNCORRELATED:
                return new CFCSUncorrelatedData(datatype, keywords);
            default:
                throw new CFCSError(CFCSIllegalValue, mode);
        }
    }

    // --------------------------------------------------------------------

    private CFCSDatatype selectDatatype()
    {
        final int type = keywords.getDatatype();

        switch (type)
        {
            case CFCSDatatype.ASCII:
                return new CFCSDatatypeASCII();
            case CFCSDatatype.FLOAT:
                return new CFCSDatatypeFloat();
            case CFCSDatatype.DOUBLE:
                return new CFCSDatatypeDouble();
            case CFCSDatatype.BINARY:
                return CFCSDatatypeBinary.getDataSubtype(getParameters());
            default:
                throw new CFCSError(CFCSIllegalValue, type);
        }
    }

    // --------------------------------------------------------------------

    private static String readFileVersion(final InputStream stream) throws IOException
    {
        final byte[] buffer = new byte[VERSION_FIELD_SIZE];

        stream.read(buffer, 0, buffer.length);

        return (new String(buffer)).trim();
    }

    // --------------------------------------------------------------------

    private static int readOffset(final InputStream stream) throws IOException
    {
        final byte[] buffer = new byte[OFFSET_FIELD_SIZE];

        stream.read(buffer, 0, buffer.length);
        final String string = (new String(buffer)).trim();

        int offset = 0;

        if (string.length() > 0)
        {
            try
            {
                offset = (new Integer(string)).intValue();
            }
            catch (NumberFormatException exception)
            {
                throw new CFCSError(CFCSBadFCS, "Malformed header offset");
            }
        }

        return offset;
    }

    // --------------------------------------------------------------------

    private void readSegments(final List<long[]> headers, final CFCSSystem.SentientInputStream stream) throws IOException
    {
        Collections.sort(headers, comparator);

        // JS
        // It is the first time we are reading segments.
        // Skip to the first segment, than reset CRC and start calculating it again
        if (bReadSegmentsFirstTime && (headers.size() > 0)) 
        {
        	long offset = stream.getFilePointer();
        	for (int i = 0; i < headers.size(); i++) {
        		long[] header = (long[]) headers.get(i);
                if (header[END] == 0)
                	continue; // Doesn't exist
                if (offset == header[BEGIN]) break;
                if (offset < header[BEGIN]) {
                    stream.skip(header[BEGIN] - offset);
                    break;
                }
        	}
        	stream.resetCRC();
        	// Now the file possition is at the first segment of the file
        	// The CRC shall be computed from the next byte up to the end the final segment
        }
        		
        
        for (int i = 0; i < headers.size(); i++)
        {
            long[] header = (long[]) headers.get(i);
            if (header[END] == 0)
                continue; // Doesn't exist

            long offset = stream.getFilePointer();
            if (header[BEGIN] < offset)
                continue; // Already read this one

            if (offset < header[BEGIN])
                stream.skip(header[BEGIN] - offset);

            long size = (header[END] - header[BEGIN]) + 1;

            if (size > Integer.MAX_VALUE)
                throw new CFCSError(CFCSNotImplemented, "Segment larger than 2G");

            segments.set((int) header[SEGMENT], readSegment(stream, (int) size));
            bReadSegmentsFirstTime = false;
        }
    }

    // --------------------------------------------------------------------

    private void writeSegments(final List<long[]> headers, final CFCSSystem.SentientOutputStream stream) throws IOException
    {
    	Collections.sort(headers, comparator);

        for (int i = 0; i < headers.size(); i++)
        {
            long[] header = (long[]) headers.get(i);
            
            if (header[END] == 0L)
                continue; // Doesn't exist?

            long offset = stream.getFilePointer();
            if (header[BEGIN] < offset)
                continue; // Already wrote this one?
            if (offset < header[BEGIN])
                stream.skip(header[BEGIN] - offset);

            writeSegment(stream, (byte[]) segments.get((int) header[SEGMENT]));
        }
    }

    // --------------------------------------------------------------------

    private static final Comparator<Object> comparator = new Comparator<Object>()
    {
        public int compare(final Object o1, final Object o2)
        {
            final long i1 = ((long[]) o1)[BEGIN];
            final long i2 = ((long[]) o2)[BEGIN];

            return (new Long(i1)).compareTo(new Long(i2));
        }
    };

    // --------------------------------------------------------------------

    private static byte[] readSegment(final InputStream stream, final int size) throws IOException
    {
        final byte[] segment = new byte[size];

        stream.read(segment);

        return segment;
    }

    // --------------------------------------------------------------------

    private static void writeSegment(final OutputStream stream, final byte[] segment) throws IOException
    {
        stream.write(segment);
    }

    // --------------------------------------------------------------------

    private static int readFileChecksum(final InputStream stream) throws IOException
    {
        final byte[] buffer = new byte[CHECKSUM_FIELD_SIZE];

        stream.read(buffer, 0, buffer.length);

        final String string = (new String(buffer)).trim();

        if (string.equals(DISABLED_CHECKSUM))
            return -1;

        int checksum = 0;

        try
        {
            checksum = (new Integer(string)).intValue();
        }
        catch (NumberFormatException exception)
        {
            throw new CFCSError(CFCSBadFCS, "Malformed checksum");
        }

        return checksum;
    }

    
    // Josef Spidlen, Feb 27, 2005 
    /*
    private static int calculateCRC(final byte[] bytes)
    {
    	sun.misc.CRC16 crc = new sun.misc.CRC16();
    	for (int i = 0; i < bytes.length; i++) 
    	{
    		crc.update(bytes[i]);
    	}
    	
    	return crc.value;
    }
    */
    	
        
    // --------------------------------------------------------------------

    private static void writeFileChecksum(final OutputStream stream, final String checksum) throws IOException
    {
        stream.write(checksum.getBytes());
    }

    // --------------------------------------------------------------------

    public final String getVersion()
    {
        return version;
    }

    public static final void setVersion(final String version)
    {
        throw new CFCSError(CFCSNotImplemented, "CFCSDataSet.setVersion(String)");
    }

    // --------------------------------------------------------------------

    public final double getVersionDoubleValue()
    {
        Double value = null;

        try
        {
            value = new Double((getVersion()).substring(VERSION_PREFIX.length()));
        }
        catch (NumberFormatException exception)
        {
            throw new CFCSError(CFCSBadValueConversion, exception);
        }

        return value.doubleValue();
    }

    public static final void setVersionDoubleValue(final double version)
    {
        throw new CFCSError(CFCSNotImplemented, "CFCSDataSet.setVersion(double)");
    }

    // --------------------------------------------------------------------

    public final int getVersionIntegerValue()
    {
        return (new Double(getVersionDoubleValue())).intValue();
    }

    public static final void setVersionIntegerValue(final int version)
    {
        throw new CFCSError(CFCSNotImplemented, "CFCSDataSet.setVersion(int)");
    }

    // --------------------------------------------------------------------

    public final int getCount()
    {
        return segments.size();
    }

    // --------------------------------------------------------------------

    public final CFCSData getData()
    {
        return data;
    }

    // --------------------------------------------------------------------

    public final CFCSKeywords getKeywords()
    {
        return keywords;
    }

    // --------------------------------------------------------------------

    public final CFCSParameters getParameters()
    {
        return new CFCSParameters(keywords);
    }

    // --------------------------------------------------------------------

    public final CFCSGatingParameters getGatingParameters()
    {
        return new CFCSGatingParameters(keywords);
    }

    // --------------------------------------------------------------------

    public final CFCSOtherSegment getOtherSegment(final int segIdx)
    {
        if (segIdx < OTHER_START || segIdx >= segments.size())
        {
            throw new CFCSError(CFCSIllegalSegment, segIdx);
        }

        CFCSOtherSegment segment = new CFCSOtherSegment();

        segment.setBytes((byte[]) segments.get(segIdx));

        return segment;
    }

    // --------------------------------------------------------------------

    public final void addOtherSegment(final CFCSOtherSegment segment)
    {
        final int count = segment.getCount();

        if (count < 1)
        {
            throw new CFCSError(CFCSInsufficientData, count);
        }

        byte[] buffer = new byte[count];

        segment.getBytes(buffer);

        segments.add(buffer);
    }

    // --------------------------------------------------------------------

    public final void addKeywords(final int segIdx)
    {
        if (segIdx < TEXT || segIdx >= segments.size())
        {
            throw new CFCSError(CFCSIllegalSegment, segIdx);
        }

        keywords.setBytes((byte[]) segments.get(segIdx), segIdx);
    }

    // --------------------------------------------------------------------

}
