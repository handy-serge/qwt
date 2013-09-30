#include "StdAfx.h"
#include "CFCSDataSet.h"
#include <assert.h>
#include <vector>
#include <limits>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "CFCSDataInteger.h"
#include "CFCSDataFloat.h"

const int CFCSDataSet::VERSION_FIELD_SIZE = 10;
const int CFCSDataSet::OFFSET_FIELD_SIZE  = 8;

// const int CFCSDataSet::HEADER      = 0;
// const int CFCSDataSet::TEXT        = 1;
// const int CFCSDataSet::DATA        = 2;
// const int CFCSDataSet::ANALYSIS    = 3;
// const int CFCSDataSet::OTHER_START = 4;

const std::string CFCSDataSet::VERSION_PREFIX  = "FCS";
const std::string CFCSDataSet::DEFAULT_VERSION = "FCS3.1";

const std::string CFCSDataSet::SEGMENT_ROOTS[CFCSDataSet::eS_SEGMENTS_COUNT] = {"HEADER", "STEXT", "DATA", "ANALYSIS"};
const std::string CFCSDataSet::SEGMENT_BEGIN_PREFIX = "$BEGIN";
const std::string CFCSDataSet::SEGMENT_END_PREFIX = "$END";

// 18 characters gives room for 1 exabytes - 1 byte...
const unsigned int CFCSDataSet::SEGMENT_SIZE_RESERVED_SPACE_SIZE = 18;


CFCSDataSet::CFCSDataSet()
{
    m_pData = new CFCSData;
}

CFCSDataSet::~CFCSDataSet(void)
{
    delete m_pData;
    m_pData = 0;
}

int CFCSDataSet::Clear()
{
    m_Headers.clear();
    m_Keywords.Clear();
    m_Segments.clear();

    return eNO_ERROR;
}

int CFCSDataSet::Read(std::istream& rStream)
{
    Clear();

    rStream.seekg(0, std::ios_base::end);
    size_t FileSize = rStream.tellg();
    rStream.seekg(0, std::ios_base::beg);

    int Error;
    Error = ReadFileVersion(rStream);
    if (Error != eNO_ERROR)
    {
        return Error;
    }

    long first = std::numeric_limits<long>::max();

    // Spec'ed segments
    for (int i = eS_TEXT; i < eS_OTHER_START; i++)
    {
        long begin;
        ReadOffset(rStream, begin);
        long end;
        ReadOffset(rStream, end);
        if ((size_t)end >= FileSize)
        {
            // Some files have an offset ending past end file
            end = FileSize - 1;
        }

        Header header = { i, begin, end };
        m_Headers.push_back(header);

        if (begin > 0L && begin < first)
            first = begin;
    }

    // Private segments
    for (int i = eS_OTHER_START; i; i++)
    {
        if (rStream.tellg() + std::istream::pos_type(2 * OFFSET_FIELD_SIZE) > first)
        {
            // There cannot be more headers because the first segment is going to start
            break;
        }

        long begin;
        ReadOffset(rStream, begin);
        long end;
        ReadOffset(rStream, end);
        if ((size_t)end >= FileSize)
        {
            // Some files have an offset ending past end file
            end = FileSize - 1;
        }
        //if((begin == 0L) || (end == 0L)) continue;

        Header header = { i, begin, end };
        m_Headers.push_back(header);


        if (begin > 0L && begin < first)
            first = begin;
    }

    if (ReadSegments(rStream) != eNO_ERROR)
    {
        return eERROR_INVALID_FILE;
    }

    m_Keywords.FillFromRawBuffer(m_Segments[eS_TEXT]);

    int Major;
    int Minor;
    GetVersion(Major, Minor);

    if (Major >= 3)
    {
        m_Headers.clear();

        // Read oversize (> 100MB) segments
        for (int i = eS_TEXT; i < eS_OTHER_START; i++)
        {
            std::string KeywordBegin = SEGMENT_BEGIN_PREFIX + SEGMENT_ROOTS[i];
            std::string KeywordEnd   = SEGMENT_END_PREFIX + SEGMENT_ROOTS[i];

            int begin = atoi(m_Keywords.GetKeywordValue(KeywordBegin).c_str());
            int end   = atoi(m_Keywords.GetKeywordValue(KeywordEnd).c_str());
            if ((size_t)end >= FileSize)
            {
                // Some files have an offset ending past end file
                end = FileSize - 1;
            }

            Header header = { i, begin, end };
            m_Headers.push_back(header);
        }
        // Clear text segment.  We already read the keywords from it and the secondary
        // text segment, if any, may add other (optional) keywords.
        m_Segments[eS_TEXT].clear();
        if (ReadSegments(rStream) != eNO_ERROR)
        {
            return eERROR_INVALID_FILE;
        }
        m_Keywords.FillFromRawBuffer(m_Segments[eS_TEXT]);
    }

    // Read the CRC
    // CR_TODO
    // ReadFileCRC(rStream);

    m_Parameters.FillFromKeywords(m_Keywords);

    ReadData(m_Segments[eS_DATA]);

    return eNO_ERROR;
}

int CFCSDataSet::ReadFileVersion(std::istream& rStream)
{
    std::vector<char> Buf(VERSION_FIELD_SIZE);

    rStream.read(&Buf[0], VERSION_FIELD_SIZE);
    if (!rStream.good())
    {
        return eERROR_INVALID_FILE;
    }

    m_Version.assign(&Buf[0], VERSION_FIELD_SIZE);

    return eNO_ERROR;
}

int CFCSDataSet::ReadOffset(std::istream& rStream, long& rOffset)
{
    std::vector<char> Buf(OFFSET_FIELD_SIZE);

    rStream.read(&Buf[0], OFFSET_FIELD_SIZE);

    if (!rStream.good())
    {
        return eERROR_INVALID_FILE;
    }

    rOffset = atoi(std::string(&Buf[0], OFFSET_FIELD_SIZE).c_str());

    return eNO_ERROR;
}

int CFCSDataSet::ReadSegments(std::istream& rStream)
{
    m_Segments.resize(m_Headers.size() + 1);

    ByteBuffer_t Buf;

    std::list<Header>::const_iterator itCur = m_Headers.begin();
    std::list<Header>::const_iterator itEnd = m_Headers.end();

    for (itCur; itCur != itEnd; ++itCur)
    {
        if (itCur->end == 0)
        {
            continue;
        }

        long size = itCur->end - itCur->begin + 1;

        if (rStream.tellg() != std::istream::pos_type(itCur->begin))
        {
            rStream.seekg(itCur->begin, std::ios_base::beg);
        }

        if (size > 0)
        {
           Buf.resize(size);
           rStream.read(reinterpret_cast<char*>(&Buf[0]), size);

           if (!rStream.good())
           {
               return eERROR_INVALID_FILE;
           }

           m_Segments[itCur->i].swap(Buf);
        }
    }

    return eNO_ERROR;
}

int CFCSDataSet::GetVersion(int& rMajor, int& rMinor)
{
    double Version = atof(m_Version.substr(VERSION_PREFIX.length(), -1).c_str());

    rMajor = static_cast<int>(Version);
    rMinor = atoi(m_Version.substr(m_Version.find_first_of(".") + 1, -1).c_str());

    return eNO_ERROR;
}

void CFCSDataSet::SetVersion(std::string version)
{
   m_Version = version;
}

int CFCSDataSet::ReadData(const ByteBuffer_t& rBuf)
{
    std::string Mode = m_Keywords.GetKeywordValue("$MODE");
    std::string Type = m_Keywords.GetKeywordValue("$DATATYPE");
    std::transform(Mode.begin(), Mode.end(), Mode.begin(), std::toupper);
    std::transform(Type.begin(), Type.end(), Type.begin(), std::toupper);

    if (Mode == "L")
    {
        if (Type == "I")
        {
            delete m_pData;
            m_pData = new CFCSDataInteger;
            m_pData->FillFromRawBuffer(rBuf, m_Keywords, m_Parameters);
        }
        else if (Type == "F")
        {
            delete m_pData;
            m_pData = new CFCSDataFloat;
            m_pData->FillFromRawBuffer(rBuf, m_Keywords, m_Parameters);
        }
        else
        {
            return eERROR_UNSUPPORTED_DATA_TYPE;
        }
    }
    else if (Mode == "C")
    {
        return eERROR_UNSUPPORTED_DATA_MODE;
    }
    else if (Mode == "U")
    {
        return eERROR_UNSUPPORTED_DATA_MODE;
    }

    return eNO_ERROR;
}

int CFCSDataSet::Write(std::ostream& rStream)
{
    m_SegmentsLocation.clear();

    WriteHeader(rStream);

    WriteTextSegment(rStream);

    WriteDataSegment(rStream);

    WriteChecksum(rStream);

    return eNO_ERROR;
}

int CFCSDataSet::WriteHeader(std::ostream& rStream)
{
    rStream.write(m_Version.c_str(), DEFAULT_VERSION.length());
    for (unsigned int i = 0; i < VERSION_FIELD_SIZE - DEFAULT_VERSION.length(); ++i)
    {
        rStream.write(" ", 1);
    }

    std::stringstream Offset;
    Offset << std::setfill(' ');
    Offset << std::setw(OFFSET_FIELD_SIZE) << 0;

    long begin;
    long end;

    // TEXT
    assert(Offset.str().length() == OFFSET_FIELD_SIZE);
    begin = rStream.tellp();
    rStream.write(Offset.str().c_str(), OFFSET_FIELD_SIZE);
    end = rStream.tellp();
    rStream.write(Offset.str().c_str(), OFFSET_FIELD_SIZE);
    m_SegmentsLocation["TEXT_BEGIN"] = begin;
    m_SegmentsLocation["TEXT_END"]   = end;

    // DATA
    begin = rStream.tellp();
    rStream.write(Offset.str().c_str(), OFFSET_FIELD_SIZE);
    end = rStream.tellp();
    rStream.write(Offset.str().c_str(), OFFSET_FIELD_SIZE);
    m_SegmentsLocation["DATA_BEGIN"] = begin;
    m_SegmentsLocation["DATA_END"]   = end;

    // ANALYSIS
    begin = rStream.tellp();
    rStream.write(Offset.str().c_str(), OFFSET_FIELD_SIZE);
    end = rStream.tellp();
    rStream.write(Offset.str().c_str(), OFFSET_FIELD_SIZE);
    m_SegmentsLocation["ANALYSIS_BEGIN"] = begin;
    m_SegmentsLocation["ANALYSIS_END"]   = end;

    return eNO_ERROR;
}

CFCSKeywords& CFCSDataSet::GetKeywords()
{
    return m_Keywords;
}

CFCSParameters& CFCSDataSet::GetParameters()
{
    return m_Parameters;
}

// CFCSData& CFCSDataSet::GetData()
// {
//     return m_Data;
// }
int CFCSDataSet::SetData(CFCSData* pData)
{
    delete m_pData;

    if (pData)
    {
        m_pData = pData;
    }
    else
    {
        m_pData = new CFCSData;
    }

    return eNO_ERROR;
}

int CFCSDataSet::WriteTextSegment(std::ostream& rStream)
{
    // 18 characters gives room for 1 exabytes - 1 byte...
    std::stringstream Temp18Zeros;
    Temp18Zeros << std::setfill(' ');
    Temp18Zeros << std::setw(SEGMENT_SIZE_RESERVED_SPACE_SIZE) << 0;

    // Add required keywords
    m_Keywords.AddKeyword("$BEGINANALYSIS", Temp18Zeros.str());
    m_Keywords.AddKeyword("$ENDANALYSIS", Temp18Zeros.str());

    m_Keywords.AddKeyword("$BEGINDATA", Temp18Zeros.str());
    m_Keywords.AddKeyword("$ENDDATA", Temp18Zeros.str());

    m_Keywords.AddKeyword("$BEGINSTEXT", Temp18Zeros.str());
    m_Keywords.AddKeyword("$ENDSTEXT", Temp18Zeros.str());

    m_Keywords.AddKeyword("$BYTEORD", "1,2,3,4");
    m_Keywords.AddKeyword("$MODE", "L");
    m_Keywords.AddKeyword("$NEXTDATA", "0");
    //m_Keywords.AddKeyword("$COM", "This is a comment containing an escape (|) value.");

    // CR_TODO:
    // Verify $PAR, $TOT, $PnB, $PnE, $PnR are present

    m_Parameters.AddToKeywords(m_Keywords);

    //m_Data.AddToKeywords(m_Keywords);
    m_pData->AddToKeywords(m_Keywords);

    std::ostream::pos_type TextBegin = rStream.tellp();
    m_Keywords.WriteToStream(rStream, m_SegmentsLocation);
    std::ostream::pos_type TextEnd = rStream.tellp() - std::istream::pos_type(1);

    std::stringstream OffsetBegin;
    OffsetBegin << std::setfill(' ');
    OffsetBegin << std::setw(OFFSET_FIELD_SIZE) << TextBegin;
    rStream.seekp(m_SegmentsLocation["TEXT_BEGIN"], std::ios_base::beg);
    assert(OffsetBegin.str().length() <= OFFSET_FIELD_SIZE);
    rStream.write(OffsetBegin.str().c_str(), OffsetBegin.str().length());

    std::stringstream OffsetEnd;
    OffsetEnd << std::setfill(' ');
    OffsetEnd << std::setw(OFFSET_FIELD_SIZE) << TextEnd;
    rStream.seekp(m_SegmentsLocation["TEXT_END"], std::ios_base::beg);
    assert(OffsetEnd.str().length() <= OFFSET_FIELD_SIZE);
    rStream.write(OffsetEnd.str().c_str(), OffsetEnd.str().length());

    // Go back to end of file
    rStream.seekp(0, std::ios_base::end);

    return eNO_ERROR;
}

int CFCSDataSet::WriteDataSegment(std::ostream& rStream)
{
    std::ostream::pos_type DataBegin = rStream.tellp();
    //m_Data.WriteToStream(rStream);
    m_pData->WriteToStream(rStream);
    std::ostream::pos_type DataEnd = rStream.tellp() - std::istream::pos_type(1);

    std::stringstream OffsetBegin;
    OffsetBegin << std::setfill(' ');
    OffsetBegin << std::setw(SEGMENT_SIZE_RESERVED_SPACE_SIZE) << DataBegin;
    rStream.seekp(m_SegmentsLocation["$BEGINDATA"], std::ios_base::beg);
    assert(OffsetBegin.str().length() <= SEGMENT_SIZE_RESERVED_SPACE_SIZE);
    rStream.write(OffsetBegin.str().c_str(), OffsetBegin.str().length());

    std::stringstream OffsetEnd;
    OffsetEnd << std::setfill(' ');
    OffsetEnd << std::setw(SEGMENT_SIZE_RESERVED_SPACE_SIZE) << DataEnd;
    rStream.seekp(m_SegmentsLocation["$ENDDATA"], std::ios_base::beg);
    assert(OffsetEnd.str().length() <= SEGMENT_SIZE_RESERVED_SPACE_SIZE);
    rStream.write(OffsetEnd.str().c_str(), OffsetEnd.str().length());

    // Go back to end of file
    rStream.seekp(0, std::ios_base::end);

    return eNO_ERROR;
}

int CFCSDataSet::WriteChecksum(std::ostream& rStream)
{
    const std::string Zeros("00000000");
    rStream.write(Zeros.c_str(), Zeros.length());

    return eNO_ERROR;
}

CFCSData* CFCSDataSet::GetData()
{
    return m_pData;
}