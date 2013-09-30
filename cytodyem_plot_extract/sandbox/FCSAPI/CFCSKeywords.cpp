#include "StdAfx.h"
#include "CFCSKeywords.h"

CFCSKeywords::CFCSKeywords(void)
{
}

CFCSKeywords::~CFCSKeywords(void)
{
}

int CFCSKeywords::FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf)
{
    if (rBuf.size() == 0)
    {
        return eERROR_INVALID_DATA;
    }

    const char Delimiter = rBuf[0];

    std::string key;
    std::string value;

    bool lastWasDelimiter = false;
    bool readingKey = true;

    for (unsigned int i = 1; i < rBuf.size(); ++i)
    {
        char ch = rBuf[i];

        if (ch == Delimiter)
        {
            if (lastWasDelimiter)
            {
                // Escaped delimiter, add it to the key/value
                (readingKey ? key : value).append(1, ch);
                lastWasDelimiter = false;
            }
            else
            {
                lastWasDelimiter = true;
            }
        }
        else
        {
            if (lastWasDelimiter)
            {
                if (!readingKey)
                {
                    std::string::size_type PosStart = key.find_first_not_of(" ");
                    std::string::size_type PosEnd   = key.find_last_not_of(" ");
                    if (PosStart != 0 || PosEnd != key.length() - 1)
                    {
                        int a = 0;
                    }
                    key = key.substr(PosStart, PosEnd - PosStart + 1);
                    m_Keywords[key] = value;
                    key.clear();
                    value.clear();
                }
                readingKey = !readingKey;
                lastWasDelimiter = false;
            }

            ((readingKey) ? key : value).append(1, ch);
        }
    }

    if (lastWasDelimiter && !readingKey)
    {
        m_Keywords[key] = value;
    }

    return eNO_ERROR;
}

int CFCSKeywords::Clear()
{
    m_Keywords.clear();

    return eNO_ERROR;
}

const std::string& CFCSKeywords::GetKeywordValue(const std::string& rKey) const
{
    static const std::string InvalidValue("");
    std::map<std::string, std::string>::const_iterator it = m_Keywords.find(rKey);

    if (it != m_Keywords.end())
    {
        return it->second;
    }
    else
    {
        return InvalidValue;
    }
}

int CFCSKeywords::AddKeyword(const std::string& rKey, const std::string& rValue)
{
    if (rValue.empty())
    {
       m_Keywords[rKey] = " ";
    }
    else
    {
       m_Keywords[rKey] = rValue;
    }

    return eNO_ERROR;
}

int CFCSKeywords::WriteToStream(std::ostream& rStream, KeywordToOffset_t& rOffsets)
{
    const std::string Separator("|");

    KeywordToValue_t::const_iterator itCur = m_Keywords.begin();
    KeywordToValue_t::const_iterator itEnd = m_Keywords.end();
    for (itCur; itCur != itEnd; ++itCur)
    {
        std::string Key = itCur->first;
        std::string Value = itCur->second;

        // Escape reserved characters in key
        std::size_t ReservedChar = Key.find_first_of(Separator);
        while (ReservedChar != std::string::npos)
        {
            Key.insert(ReservedChar, Separator);
            ReservedChar = Key.find_first_of(Separator, ReservedChar + 2);
        }

        // Escape reserved characters in value
        ReservedChar = Value.find_first_of(Separator);
        while (ReservedChar != std::string::npos)
        {
            Value.insert(ReservedChar, Separator);
            ReservedChar = Value.find_first_of(Separator, ReservedChar + 2);
        }

        rStream.write(Separator.c_str(), Separator.length());
        rStream.write(Key.c_str(), Key.length());
        rStream.write(Separator.c_str(), Separator.length());

        // Save the stream position where the value for the given key is written
        // to allow to later write the proper offsets for supplementary segments.
        rOffsets[itCur->first] = rStream.tellp();
        rStream.write(Value.c_str(), Value.length());
    }

    rStream.write(Separator.c_str(), Separator.length());

    return eNO_ERROR;
}
