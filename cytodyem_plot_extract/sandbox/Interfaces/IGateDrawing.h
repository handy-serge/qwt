#pragma once

using namespace System;
using namespace NationalInstruments::UI::WindowsForms;
using namespace NationalInstruments::UI;


namespace GateDrawing {

public interface class IPlotGate
{
    bool IsPointInside(double X, double Y);

//    static IPlotGate(){};
};

public delegate void GateChangedHandler();

public interface struct IGateDrawing
{
    event GateChangedHandler^ GateChanged;
    int Attach(
        NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
        NationalInstruments::UI::XYPlot^ Plot);
    IPlotGate^ GetCurrentGate();

//    static IGateDrawing(){};
};

}


