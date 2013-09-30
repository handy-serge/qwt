#include "StdAfx.h"
#include "CFCSData.h"
#include <sstream>
#include "CFCSKeywords.h"
#include "CFCSParameters.h"

CFCSData::CFCSData(void)
{
}

CFCSData::~CFCSData(void)
{
}

int CFCSData::WriteToStream(std::ostream& rStream)
{
    return eNO_ERROR;
}

int CFCSData::FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf,
                                const CFCSKeywords& rKeywords,
                                const CFCSParameters& rParameters)
{
    return eNO_ERROR;
}

int CFCSData::AddToKeywords(CFCSKeywords& rKeywords)
{
    if (GetNumData() == 0)
    {
        return eERROR_INVALID_DATA;
    }

    std::stringstream ToStringConv;
    ToStringConv.clear(); ToStringConv << GetNumData();
    rKeywords.AddKeyword("$TOT", ToStringConv.str());

    return eNO_ERROR;
}

size_t CFCSData::GetNumData()
{
    return 0;
}
