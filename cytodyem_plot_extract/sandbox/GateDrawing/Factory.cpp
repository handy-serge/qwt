#include "stdafx.h"
#include "Factory.h"
#include "RectangleMarker.h"
#include "VerticalRectangleMarker.h"

namespace GateDrawing
{;

IGateDrawing^ Factory::createGateDrawingForHistogram()
{
    return gcnew VerticalRectangleMarker();
}

}

GateDrawing::IGateDrawing^ GateDrawing::Factory::createGateDrawingForScatterPlot()
{
    return gcnew RectangleMarker();
}
