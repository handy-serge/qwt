#include "StdAfx.h"
#include "Peak.h"


Peak::Peak()
: m_Height(0.0)
, m_Width(0.0)
, m_TimeStamp(-1)
{
}


double Peak::GetCompensatedHeight() const
{
   return m_CompensatedHeight;
}


double Peak::GetHeight() const
{
   return m_Height;
}


double Peak::GetWidth() const
{
   return m_Width;
}