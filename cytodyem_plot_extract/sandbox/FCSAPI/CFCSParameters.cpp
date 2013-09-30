#include "StdAfx.h"
#include <sstream>
#include <assert.h>
#include "CFCSParameters.h"

const std::string CFCSParameters::DATA_PREFIX = "$P";

const CFCSParameters::DataProperties CFCSParameters::DATA_PROPERTIES[] =
{
    CFCSParameters::DataProperties("S", "FullName",               false),
    CFCSParameters::DataProperties("N", "ShortName",              false),
    CFCSParameters::DataProperties("B", "FieldSizeString",        true ),
    CFCSParameters::DataProperties("R", "Range",                  true ),
    CFCSParameters::DataProperties("G", "Gain",                   false),
    CFCSParameters::DataProperties("F", "Filter",                 false),
    CFCSParameters::DataProperties("L", "ExcitationWavelength",   false),
    CFCSParameters::DataProperties("O", "LaserPower",             false),
    CFCSParameters::DataProperties("P", "EmittedPercent",         false),
    CFCSParameters::DataProperties("V", "Voltage",                false),
    CFCSParameters::DataProperties("T", "DetectorType",           false),
    CFCSParameters::DataProperties("E", "LogDecadesAndOffset",    true ),
    CFCSParameters::DataProperties("D", "PreferredDisplay",       false),
    CFCSParameters::DataProperties("Calibration", "Calibration",  false)
};

CFCSParameters::CFCSParameters(void)
{
}

CFCSParameters::~CFCSParameters(void)
{
}

int CFCSParameters::FillFromKeywords(const CFCSKeywords& rKeywords)
{
    int NumParameters = atoi(rKeywords.GetKeywordValue("$PAR").c_str());
    m_Parameters.resize(NumParameters);

    for (int i = 0; i < NumParameters; ++i)
    {
        std::stringstream Index;
        Index << i + 1;

        for (int p = 0; p < CFCSParameter::eP_COUNT; ++p)
        {
            const std::string& Value = rKeywords.GetKeywordValue(DATA_PREFIX + Index.str() + DATA_PROPERTIES[p].ParameterCode);
            m_Parameters[i].SetProperty(p, Value);
        }
    }

    return eNO_ERROR;
}

int CFCSParameters::NumParams() const
{
    return m_Parameters.size();
}

const CFCSParameter& CFCSParameters::GetParam(int ParamIndex) const
{
    static const CFCSParameter NullParam;
    if (ParamIndex < static_cast<int>(m_Parameters.size()))
    {
        return m_Parameters[ParamIndex];
    }
    else
    {
        return NullParam;
    }
}

int CFCSParameters::AddParameter(const CFCSParameter& rParam)
{
    m_Parameters.push_back(rParam);

    return eNO_ERROR;
}

int CFCSParameters::AddToKeywords(CFCSKeywords& rKeywords)
{
    std::stringstream ToStringConv;
    ToStringConv.clear(); ToStringConv << m_Parameters.size();
    rKeywords.AddKeyword("$PAR", ToStringConv.str());

    for (unsigned int i = 0; i < m_Parameters.size(); ++i)
    {
        for (int p = 0; p < CFCSParameter::eP_COUNT; ++p)
        {
            const CFCSParameter& rParam = m_Parameters[i];
            if (rParam.GetProperty(p) != "")
            {
                std::stringstream Index;
                Index << i + 1;
                rKeywords.AddKeyword(DATA_PREFIX + Index.str() + DATA_PROPERTIES[p].ParameterCode, rParam.GetProperty(p));
            }
        }
    }

    return eNO_ERROR;
}
