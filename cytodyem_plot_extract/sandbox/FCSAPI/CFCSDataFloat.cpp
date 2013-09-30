#include "StdAfx.h"
#include "CFCSDataFloat.h"
#include <sstream>
#include "CFCSKeywords.h"
#include "CFCSParameters.h"

CFCSDataFloat::CFCSDataFloat(void)
{
}

CFCSDataFloat::~CFCSDataFloat(void)
{
}

int CFCSDataFloat::AddData(const ListData_t& rData)
{
    m_Data.push_back(rData);

    return eNO_ERROR;
}

int CFCSDataFloat::WriteToStream(std::ostream& rStream)
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

int CFCSDataFloat::AddToKeywords(CFCSKeywords& rKeywords)
{
    if (CFCSData::AddToKeywords(rKeywords) != eNO_ERROR)
    {
        return eERROR_INVALID_DATA;
    }

    rKeywords.AddKeyword("$DATATYPE", "F");

    return eNO_ERROR;
}


int CFCSDataFloat::FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf, const CFCSKeywords& rKeywords, const CFCSParameters& rParameters)
{
    int NumEvents = atoi(rKeywords.GetKeywordValue("$TOT").c_str());

    std::vector<unsigned int> ParamSizeInBytes(rParameters.NumParams());

    for (int p = 0; p < rParameters.NumParams(); ++p)
    {
        const CFCSParameter& rParam = rParameters.GetParam(p);
        int SizeInBits = atoi(rParam.GetProperty(CFCSParameter::eP_FIELDSIZESTRING).c_str());

        if (SizeInBits == 0 || SizeInBits % 8 != 0)
        {
            return eERROR_UNSUPPORTED_PARAMETER_BITS_SIZE;
        }

        ParamSizeInBytes[p] = SizeInBits / 8;
    }

    std::vector<ListData_t> EventData(rParameters.NumParams());

    // CR_TODO: Use $BYTEORD to read using the correct endianness
    int ReadIndex = 0;
    for (int e = 0; e < NumEvents; ++e)
    {
        for (int p = 0; p < rParameters.NumParams(); ++p)
        {
            unsigned int Data = 0;
            for (unsigned int b = 0; b < ParamSizeInBytes[p]; ++b)
            {
                Data |= rBuf[ReadIndex] << (b * 8);
                ++ReadIndex;
            }

            EventData[p].push_back(*(float*)&Data);
        }
    }

    for (int p = 0; p < rParameters.NumParams(); ++p)
    {
        AddData(EventData[p]);
    }

    return eNO_ERROR;
}


const CFCSDataFloat::ListData_t& CFCSDataFloat::GetData(unsigned int Index)
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