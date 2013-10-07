#pragma once

namespace CustomControls
{;

public ref class MarkerTypeChangedEventArgs: EventArgs
{
public:
    property GateDrawing::PlotMarkerType MarkerType;
    MarkerTypeChangedEventArgs(GateDrawing::PlotMarkerType markerType)
    {
        MarkerType = markerType;
    };

};

}