#include "StdAfx.h"
#include "CFCSDataInteger.h"
#include <sstream>
#include "CFCSKeywords.h"
#include "CFCSParameters.h"

CFCSDataInteger::CFCSDataInteger(void)
{
}

CFCSDataInteger::~CFCSDataInteger(void)
{
}

int CFCSDataInteger::AddData(const ListData_t& rData)
{
    m_Data.push_back(rData);

    return eNO_ERROR;
}

int CFCSDataInteger::WriteToStream(std::ostream& rStream)
{
    if (m_Data.size() == 0)
    {
        return eERROR_INVALID_DATA;
    }

    for (unsigned int r = 0; r < m_Data[0].size(); ++r)
    {
        for (unsigned int c = 0; c < m_Data.size(); ++c)
        {
            rStream.write(reinterpret_cast<const char*>(&m_Data[c][r]), sizeof(unsigned int));
        }
    }

    return eNO_ERROR;
}

int CFCSDataInteger::AddToKeywords(CFCSKeywords& rKeywords)
{
    if (CFCSData::AddToKeywords(rKeywords) != eNO_ERROR)
    {
        return eERROR_INVALID_DATA;
    }

    rKeywords.AddKeyword("$DATATYPE", "I");

    return eNO_ERROR;
}

int CFCSDataInteger::FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf,
                                       const CFCSKeywords& rKeywords,
                                       const CFCSParameters& rParameters)
{
    int NumEvents = atoi(rKeywords.GetKeywordValue("$TOT").c_str());

    std::vector<unsigned int> ParamSizeInBytes(rParameters.NumParams());
    std::vector<unsigned int> ParamBitMask(rParameters.NumParams());

    for (int p = 0; p < rParameters.NumParams(); ++p)
    {
        const CFCSParameter& rParam = rParameters.GetParam(p);
        int SizeInBits = atoi(rParam.GetProperty(CFCSParameter::eP_FIELDSIZESTRING).c_str());
        if (SizeInBits == 0 || SizeInBits % 8 != 0)
        {
            return eERROR_UNSUPPORTED_PARAMETER_BITS_SIZE;
        }
        ParamSizeInBytes[p] = SizeInBits / 8;

        std::stringstream StringToNumber;
        StringToNumber << rParam.GetProperty(CFCSParameter::eP_RANGE);
        unsigned __int64 Range;
        StringToNumber >> Range;
        if (Range == 0 || Range - 2 >= UINT_MAX)
        {
            return eERROR_UNSUPPORTED_PARAMETER_RANGE;
        }
        ParamBitMask[p] = static_cast<unsigned int>(Range - 1);
    }

    std::vector<ListData_t> EventData(rParameters.NumParams());

    // CR_TODO: Use $BYTEORD to read using the correct endianness
    int ReadIndex = 0;
    for (int e = 0; e < NumEvents; ++e)
    {
        for (int p = 0; p < rParameters.NumParams(); ++p)
        {
            unsigned int Data = 0;
            unsigned int Data2 = 0;
            for (unsigned int b = 0; b < ParamSizeInBytes[p]; ++b)
            {
                Data += rBuf[ReadIndex] << (b * 8);
                Data2 |= rBuf[ReadIndex] << (b * 8);
                ++ReadIndex;
            }
            //Data &= ParamBitMask[p];
            while (Data > ParamBitMask[p])
            {
                Data -= ParamBitMask[p];
            }

            EventData[p].push_back(Data);
        }
    }

    for (int p = 0; p < rParameters.NumParams(); ++p)
    {
        AddData(EventData[p]);
    }

    return eNO_ERROR;
}

const CFCSDataInteger::ListData_t& CFCSDataInteger::GetData(unsigned int Index)
{
    static const ListData_t NoData;

    if (Index < m_Data.size())
    {
        return m_Data[Index];
    }
    else
    {
        return NoData;
    }
}