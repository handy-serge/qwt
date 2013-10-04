/*
* Copyright 2012 (c) handyem inc. All rights reserved.
*/
#pragma once

#using "Interfaces.dll"

namespace GateDrawing
{;
public ref class PlotGate: public IPlotGate
{
public:
   PlotGate();

   virtual bool IsPointInside(double X, double Y);
};

public ref class PlotGateRect : PlotGate
{
public:
   PlotGateRect();

   int SetRect(float left, float top, float right, float bottom);

   virtual bool IsPointInside(double X, double Y) override;

protected:
   System::Drawing::RectangleF m_Rect;
};

}