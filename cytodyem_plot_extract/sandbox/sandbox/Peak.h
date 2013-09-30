#pragma once


struct Peak
{
   Peak();

   typedef double (Peak::*PeakMemFn)() const;
   double GetCompensatedHeight() const;
   double GetHeight() const;
   double GetWidth() const;


   unsigned int m_TimeStamp;
   double m_Height;
   double m_Width;
   double m_CompensatedHeight;
};
