#pragma once
#using "Interfaces.dll"


namespace GateDrawing
{
    public ref class Factory
    {
    public:
        static IGateDrawing^ CreateGateDrawing(GateDrawing::PlotMarkerType markerType);
    };
}
