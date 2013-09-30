#pragma once
#include <vector>
#include <ostream>
#include "CFCSData.h"
#include "CFCSKeywords.h"

class CFCSDataInteger : public CFCSData
{
public:
    CFCSDataInteger(void);
    ~CFCSDataInteger(void);

    enum eError
    {
        eNO_ERROR,
        eERROR_INVALID_DATA
    };

    typedef unsigned int Data_t;
    typedef std::vector<Data_t> ListData_t;

    virtual int FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf,
                                  const CFCSKeywords& rKeywords,
                                  const CFCSParameters& rParameters);

    virtual int WriteToStream(std::ostream& rStream);
    virtual int AddToKeywords(CFCSKeywords& rKeywords);

    int AddData(const ListData_t& rData);

    virtual size_t GetNumData() { return m_Data[0].size(); }

    const ListData_t& GetData(unsigned int Index);

protected:
    std::vector<ListData_t> m_Data;
};
