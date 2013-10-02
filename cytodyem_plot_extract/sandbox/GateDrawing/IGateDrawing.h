#pragma once

namespace GateDrawing
{;

ref class PlotGate;
ref class PlotGateRect;

public delegate void GateChangedHandler();

public interface struct IGateDrawing
{
    event GateChangedHandler^ GateChanged;
    int Attach(
        NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
        NationalInstruments::UI::XYPlot^ Plot);

    // Factory methods that will return something that can draw gates on screen.
    static IGateDrawing^ createGateDrawingForHistogram();
    static IGateDrawing^ createGateDrawingForScatterPlot();
    PlotGate^ GetCurrentGate();
};

}


