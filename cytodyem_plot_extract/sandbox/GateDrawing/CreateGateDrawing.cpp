#include "stdafx.h"
#include "IGateDrawing.h"
#include "GateDrawing.h"
#include "GateDrawingByXAxisRectangle.h"

namespace GateDrawing
{;

IGateDrawing^ IGateDrawing::createGateDrawingForHistogram()
{
    return gcnew GateDrawingByXAxisRectangle();
}

}

GateDrawing::IGateDrawing^ GateDrawing::IGateDrawing::createGateDrawingForScatterPlot()
{
    return gcnew GateDrawing();
}
