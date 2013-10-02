#include "stdafx.h"
#include "IGateDrawing.h"
#include "GateDrawing.h"
#include "GateDrawingByXAxisRectangle.h"

namespace GateDrawing
{;

IGateDrawing^ IGateDrawing::createGateDrawingForHistogram()
{
    return gcnew VerticalRectangleMarker();
}

}

GateDrawing::IGateDrawing^ GateDrawing::IGateDrawing::createGateDrawingForScatterPlot()
{
    return gcnew GateDrawing();
}
