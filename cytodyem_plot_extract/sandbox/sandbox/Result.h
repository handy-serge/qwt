#pragma once

#include "Peak.h"
#include <vector>

class Result
{
    public:
        Result();
        ~Result();

        int Clear();
        void SetVolume(double volume);
        Peak* AddPeak(const Peak& rPeak);

        std::vector<Peak> m_ListPeaks;

    private:
        double m_Volume;
};