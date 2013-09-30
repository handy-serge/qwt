#pragma once
#include <map>
#include <vector>
#include <string>
#include "CFCSDataTypes.h"

class CFCSKeywords
{
public:
    enum eError
    {
        eNO_ERROR,
        eERROR_INVALID_DATA
    };

    CFCSKeywords(void);
    ~CFCSKeywords(void);

    typedef std::map<std::string, std::string> KeywordToValue_t;
    typedef std::map<std::string, size_t> KeywordToOffset_t;

    int FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf);
    int WriteToStream(std::ostream& rStream, KeywordToOffset_t& rOffsets);

    int Clear();

    int AddKeyword(const std::string& rKey, const std::string& rValue);

    const std::string& GetKeywordValue(const std::string& rKey) const;

protected:


    std::map<std::string, std::string> m_Keywords;
};
