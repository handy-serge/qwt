#pragma once

#include "CFCSDataSet.h"
#include "Result.h"
#include <fstream>
#include <vector>

using namespace System;

public ref class ImportFile
{
    public:
        ImportFile();
        ~ImportFile();

        void LoadFCS(String^ fileNameAndPath, unsigned int nbchannel, std::vector<Result>& Results);

    private:
        std::string toStdString(String ^ inputString);
        void readFcsFile(CFCSDataSet& DataSet);
        int import(CFCSDataSet& Data, std::vector<Result>& Results);

        unsigned int m_NbChannel;
        String^ m_FileNameAndPath;
};

