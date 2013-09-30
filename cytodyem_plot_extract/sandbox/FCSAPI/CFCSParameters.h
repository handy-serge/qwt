#pragma once
#include <string>
#include "CFCSKeywords.h"
#include "CFCSParameter.h"

class CFCSParameters
{
public:
    enum eError
    {
        eNO_ERROR,
    };

    CFCSParameters(void);
    ~CFCSParameters(void);

    struct DataProperties
    {
        DataProperties(const std::string& rC, const std::string& rP, bool rR)
            : ParameterCode(rC), ParameterProperty(rP), ParameterRequired(rR) { }

        std::string ParameterCode;
        std::string ParameterProperty;
        bool        ParameterRequired;
    };

    typedef std::vector<CFCSParameter> ListParameters_t;

    static const std::string DATA_PREFIX;
    static const DataProperties DATA_PROPERTIES[];

    int FillFromKeywords(const CFCSKeywords& rKeywords);
    int AddToKeywords(CFCSKeywords& rKeywords);

    int NumParams() const;
    const CFCSParameter& GetParam(int ParamIndex) const;
    int AddParameter(const CFCSParameter& rParam);

protected:
    ListParameters_t m_Parameters;
};
