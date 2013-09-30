#include "StdAfx.h"
#include "Result.h"

Result::Result()
{
}


Result::~Result()
{
}


int Result::Clear()
{
//   m_ListPeaks.clear();

   return 0;
}


void Result::SetVolume(double volume)
{
   m_Volume = System::Math::Max(volume, 0.0);
}


Peak* Result::AddPeak(const Peak& rPeak)
{
   int Index = m_ListPeaks.size();
   m_ListPeaks.push_back(rPeak);
   Peak* pPeak = &m_ListPeaks.back();

   return pPeak;
}