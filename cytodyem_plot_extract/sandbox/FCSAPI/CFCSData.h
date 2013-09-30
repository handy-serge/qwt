#pragma once
#include <vector>
#include <ostream>
#include "CFCSDataTypes.h"

class CFCSKeywords;
class CFCSParameters;

class CFCSData
{
public:
    CFCSData(void);
    ~CFCSData(void);

    enum eError
    {
        eNO_ERROR,
        eERROR_INVALID_DATA,
        eERROR_UNSUPPORTED_PARAMETER_BITS_SIZE,
        eERROR_UNSUPPORTED_PARAMETER_RANGE
    };

    virtual int FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf,
                                  const CFCSKeywords& rKeywords,
                                  const CFCSParameters& rParameters);

    virtual int AddToKeywords(CFCSKeywords& rKeywords);
    virtual int WriteToStream(std::ostream& rStream);

    virtual size_t GetNumData();

protected:
};
