#include "StdAfx.h"
#include "ImportFile.h"
#include <FCSAPI/CFCSDataFloat.h>
#include "Peak.h"

using namespace System::Runtime::InteropServices;

ImportFile::ImportFile()
{
}


ImportFile::~ImportFile()
{
}


void ImportFile::LoadFCS(String^ fileNameAndPath, unsigned int nbChannel, std::vector<Result>& results)
{
    bool Success = false;
    String^ ext;

    m_NbChannel = nbChannel;
    m_FileNameAndPath = fileNameAndPath;

    ext = System::IO::Path::GetExtension(m_FileNameAndPath);

    if (ext == ".fcs")
    {
        // Extract data from the FCS file.
        CFCSDataSet DataSet;
        readFcsFile(DataSet);

        // Prepare data structure to hold extracted data.
        results.resize(m_NbChannel);
        for (unsigned int i = 0; i < m_NbChannel; ++i)
        {
            results[i].Clear();
        }

        // Copy extracted data in our data structure.
        import(DataSet, results);
    }
    else
    {
        System::Windows::Forms::MessageBox::Show("Unknown file extension specified.", "Error",
                                                System::Windows::Forms::MessageBoxButtons::OK,
                                                System::Windows::Forms::MessageBoxIcon::Error);
    }
}


std::string ImportFile::toStdString(String ^ inputString)
{
   char* tmp = (char*) Marshal::StringToHGlobalAnsi(inputString).ToPointer();

   std::string s(tmp);
   Marshal::FreeHGlobal(IntPtr(tmp));

   return s;
}


void ImportFile::readFcsFile(CFCSDataSet& DataSet)
{
    std::ifstream InputStream;
    InputStream.open(toStdString(m_FileNameAndPath), std::ios_base::binary);

    DataSet.Read(InputStream);
}


int ImportFile::import(CFCSDataSet& dataSet, std::vector<Result>& results)
{
    unsigned int NumPars = atoi(dataSet.GetKeywords().GetKeywordValue("$PAR").c_str());
    unsigned int NumEvents = atoi(dataSet.GetKeywords().GetKeywordValue("$TOT").c_str());

    double heightScale;
    String^ heightScaleString = gcnew String(dataSet.GetKeywords().GetKeywordValue("HeightSCALE").c_str());
    if (heightScaleString != "")
    {
        heightScale = Convert::ToDouble(heightScaleString);
    }
    else
    {
        heightScale = 10000.0;
    }

    double volume;
    String^ volumeString = gcnew String(dataSet.GetKeywords().GetKeywordValue("$VOL").c_str());
    try
    {
        volume = Convert::ToDouble(volumeString) / 1000000.0; //convert from nano to mili L
    }
    catch (...)
    {
        volume = 0.0;
    }

    std::map<std::string, unsigned int> ShortNameToParam;
    std::map<std::string, unsigned int>::const_iterator itParam;
    std::vector<const CFCSDataFloat::ListData_t*> ChannelDataHeight(m_NbChannel);

    CFCSDataFloat::ListData_t const* pTimeStamps = nullptr;
    CFCSDataFloat::ListData_t const* pDataWidth = nullptr;

    CFCSDataFloat* pData = reinterpret_cast<CFCSDataFloat*>(dataSet.GetData());

    for (unsigned int i = 0; i < NumPars; ++i)
    {
        const CFCSParameter& rParam = dataSet.GetParameters().GetParam(i);

        ShortNameToParam[rParam.GetProperty(CFCSParameter::eP_SHORTNAME)] = i;

        if ("TS" != rParam.GetProperty(CFCSParameter::eP_SHORTNAME) 
        && "Width" != rParam.GetProperty(CFCSParameter::eP_SHORTNAME)
        && i < m_NbChannel)
        {
        ChannelDataHeight[i] = &pData->GetData(i);
        }
    }

    // Find timestamp
    itParam = ShortNameToParam.find("TS");
    if (itParam != ShortNameToParam.end())
    {
        pTimeStamps = &pData->GetData(itParam->second);
    }
    else
    {
        // Error
        return -1;
    }

    // Find Width Data
    itParam = ShortNameToParam.find("Width");
    if (itParam != ShortNameToParam.end())
    {
        pDataWidth = &pData->GetData(itParam->second);
    }
    else
    {
        // Error
        return -1;
    }

    for (unsigned int c = 0; c < m_NbChannel; ++c)
    {
        if (ChannelDataHeight[c] == 0)
        {
            continue;
        }

        results[c].SetVolume(volume);
     
        for (unsigned int i = 0; i < NumEvents; ++i)
        {
            Peak NewPeak;

            // Undo rescaling done when exporting to FCS
            NewPeak.m_Height = (*ChannelDataHeight[c])[i]/* / heightScale*/;
            NewPeak.m_Width     = static_cast<unsigned int>((*pDataWidth)[i]);
            NewPeak.m_TimeStamp = static_cast<unsigned int>((*pTimeStamps)[i]);
            results[c].AddPeak(NewPeak);
        }
    }

    return 0;
}
