#pragma once

using namespace System;
using namespace NationalInstruments::UI::WindowsForms;
using namespace NationalInstruments::UI;


namespace GateDrawing {

public interface class IPlotGate
{
    bool IsPointInside(double X, double Y);
};

public delegate void GateChangedHandler();

public interface struct IGateDrawing
{
    event GateChangedHandler^ GateChanged;
    void Attach(
        NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
        NationalInstruments::UI::XYPlot^ Plot);

    void Detach();

	void eraseMarker();
    IPlotGate^ GetCurrentGate();
};

public enum class PlotMarkerType
{
    Rectangle
    , Stripe
    , Polygon
};

}


