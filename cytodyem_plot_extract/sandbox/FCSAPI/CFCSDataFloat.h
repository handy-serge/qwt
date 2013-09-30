#pragma once
#include <vector>
#include <ostream>
#include "CFCSData.h"
#include "CFCSKeywords.h"

class CFCSDataFloat : public CFCSData
{
public:
    CFCSDataFloat(void);
    ~CFCSDataFloat(void);

    enum eError
    {
        eNO_ERROR,
        eERROR_INVALID_DATA
    };

    typedef float Data_t;
    typedef std::vector<Data_t> ListData_t;

    virtual int FillFromRawBuffer(const CFCSDataTypes::ByteBuffer_t& rBuf,
                                  const CFCSKeywords& rKeywords,
                                  const CFCSParameters& rParameters);

    virtual int WriteToStream(std::ostream& rStream);
    virtual int AddToKeywords(CFCSKeywords& rKeywords);

    int AddData(const ListData_t& rData);

    virtual size_t GetNumData() 
    {
       if (m_Data.size() > 0)
       {
         return m_Data[0].size();
       }
       else
       {
          return 0;
       }
    }

    const ListData_t& GetData(unsigned int Index);

protected:
    std::vector<ListData_t> m_Data;
};
