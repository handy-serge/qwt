/*
* Copyright 2012 (c) handyem inc. All rights reserved.
*/
#include "StdAfx.h"
#include "PlotGate.h"

namespace GateDrawing
{;

PlotGate::PlotGate()
{

}

PlotGateRect::PlotGateRect()
{

}

bool PlotGateRect::IsPointInside(double X, double Y)
{
   return m_Rect.Contains((float)X, (float)Y);
}

int PlotGateRect::SetRect(float left, float top, float right, float bottom)
{
   m_Rect.X = left;
   m_Rect.Y = top;
   m_Rect.Width = right - left;
   m_Rect.Height = bottom - top;

   return 0;
}

}