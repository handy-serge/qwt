#pragma once

#include <iosfwd>
#include <string>
#include <list>
#include <vector>
#include "CFCSDataTypes.h"
#include "CFCSKeywords.h"
#include "CFCSParameters.h"
#include "CFCSData.h"

class CFCSDataSet
{
public:
    struct Header
    {
        long i;
        long begin;
        long end;
    };

    static const int VERSION_FIELD_SIZE;
    static const int OFFSET_FIELD_SIZE;

    enum eSegments
    {
        eS_HEADER   = 0,
        eS_TEXT     = 1,
        eS_DATA     = 2,
        eS_ANALYSIS = 3,

        eS_SEGMENTS_COUNT,
    };

    enum eOtherSegments
    {
        eS_OTHER_START = eS_SEGMENTS_COUNT,
    };

//     static const int HEADER;
//     static const int TEXT;
//     static const int DATA;
//     static const int ANALYSIS;
//     static const int OTHER_START;

    static const std::string VERSION_PREFIX;
    static const std::string DEFAULT_VERSION;

    static const std::string SEGMENT_ROOTS[eS_SEGMENTS_COUNT];
    static const std::string SEGMENT_BEGIN_PREFIX;
    static const std::string SEGMENT_END_PREFIX;

    static const unsigned int SEGMENT_SIZE_RESERVED_SPACE_SIZE;


    enum eError
    {
        eNO_ERROR,
        eERROR_INVALID_FILE,
        eERROR_UNSUPPORTED_DATA_MODE,
        eERROR_UNSUPPORTED_DATA_TYPE,
    };

    CFCSDataSet();
    virtual ~CFCSDataSet(void);

    int Read(std::istream& rStream);
    int Write(std::ostream& rStream);
    int Clear();

    int GetVersion(int& rMajor, int& rMinor);
    void SetVersion(std::string version);

    CFCSKeywords& GetKeywords();
    CFCSParameters& GetParameters();
    CFCSData* GetData();
    int SetData(CFCSData* pData);

protected:
    typedef CFCSDataTypes::ByteBuffer_t ByteBuffer_t;

    int ReadFileVersion(std::istream& rStream);
    int ReadOffset(std::istream& rStream, long& rOffset);
    int ReadSegments(std::istream& rStream);
    int ReadData(const CFCSDataTypes::ByteBuffer_t& rBuf);
    int WriteHeader(std::ostream& rStream);
    int WriteTextSegment(std::ostream& rStream);
    int WriteDataSegment(std::ostream& rStream);
    int WriteChecksum(std::ostream& rStream);
protected:

    std::string                 m_Version;
    std::list<Header>           m_Headers;
    std::vector<ByteBuffer_t>   m_Segments;

    CFCSKeywords                m_Keywords;
    CFCSParameters              m_Parameters;
    CFCSData*                   m_pData;

    // Write offsets
    CFCSKeywords::KeywordToOffset_t m_SegmentsLocation;

};
