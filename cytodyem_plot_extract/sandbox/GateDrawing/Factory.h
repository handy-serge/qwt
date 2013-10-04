#pragma once
#using "Interfaces.dll"


namespace GateDrawing
{
    public ref class Factory
    {
    public:
        static IGateDrawing^ createGateDrawingForHistogram();
        static IGateDrawing^ createGateDrawingForScatterPlot();
    };
}
