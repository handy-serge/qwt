#pragma once
#include <string>
#include <vector>

class CFCSParameter
{
public:
    enum eError
    {
        eNO_ERROR,
        eINVALID_PROPERTY
    };

    enum eProperty
    {
        eP_FULLNAME,
        eP_SHORTNAME,
        eP_FIELDSIZESTRING,
        eP_RANGE,
        eP_GAIN,
        eP_FILTER,
        eP_EXCITATIONWAVELENGTH,
        eP_LASERPOWER,
        eP_EMITTEDPERCENT,
        eP_VOLTAGE,
        eP_DETECTORTYPE,
        eP_LOGDECADESANDOFFSET,
        eP_PREFERREDDISPLAY,

        eP_COUNT
    };

    CFCSParameter(void);
    ~CFCSParameter(void);

    int SetProperty(int Prop, const std::string& rValue);
    const std::string& GetProperty(int Prop) const;

protected:
    std::vector<std::string> m_Properties;
};
