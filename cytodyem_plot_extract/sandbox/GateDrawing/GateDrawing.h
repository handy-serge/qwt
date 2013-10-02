#pragma once

#include "IGateDrawing.h"

#using "System.Windows.Forms.dll"
#using "System.Drawing.dll"


namespace GateDrawing
{;

ref class PlotGate;
ref class PlotGateRect;

ref class GateDrawing: public IGateDrawing
{
public:
    GateDrawing();

    virtual event GateChangedHandler^ GateChanged;

    virtual int Attach(
        NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
        NationalInstruments::UI::XYPlot^ Plot);

    virtual PlotGate^ GetCurrentGate();


private:
    void ButtonDown(
        System::Object^ sender,
        System::Windows::Forms::MouseEventArgs^ e);

    void ButtonUp(
        System::Object^ sender,
        System::Windows::Forms::MouseEventArgs^ e);

    void MouseMove(
        System::Object^ sender,
        System::Windows::Forms::MouseEventArgs^ e);

    void BeforeDrawPlot(
        System::Object^ sender,
        NationalInstruments::UI::BeforeDrawXYPlotEventArgs^ e);


    NationalInstruments::UI::WindowsForms::XYGraph^ m_Graph;
    NationalInstruments::UI::XYPlot^ m_Plot;

    System::Drawing::RectangleF m_Gate;
    System::Drawing::Rectangle m_Rect;
    PlotGateRect^ m_CurrentGate;

    bool m_ButtonDownPlot;
    System::Drawing::Point m_Pt0;
    System::Drawing::Point m_Pt1;
};

};