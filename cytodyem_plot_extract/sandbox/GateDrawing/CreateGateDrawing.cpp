#include "stdafx.h"
#include "IGateDrawing.h"
#include "RectangleMarker.h"
#include "VerticalRectangleMarker.h"

namespace GateDrawing
{;

IGateDrawing^ IGateDrawing::createGateDrawingForHistogram()
{
    return gcnew VerticalRectangleMarker();
}

}

GateDrawing::IGateDrawing^ GateDrawing::IGateDrawing::createGateDrawingForScatterPlot()
{
    return gcnew RectangleMarker();
}
