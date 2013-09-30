#include "StdAfx.h"
#include "CFCSParameter.h"

CFCSParameter::CFCSParameter(void)
{
    m_Properties.resize(eP_COUNT);
}

CFCSParameter::~CFCSParameter(void)
{
}

int CFCSParameter::SetProperty(int Prop, const std::string& rValue)
{
    if (Prop >= eP_COUNT)
    {
        return eINVALID_PROPERTY;
    }

    m_Properties[Prop] = rValue;

    return eNO_ERROR;
}

const std::string& CFCSParameter::GetProperty(int Prop) const
{
    static const std::string NullProperty;

    if (Prop < eP_COUNT)
    {
        return m_Properties[Prop];
    }
    else
    {
        return NullProperty;
    }
}
