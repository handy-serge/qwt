#pragma once

#using "Interfaces.dll"
#using "System.Windows.Forms.dll"
#using "System.Drawing.dll"

#include "PlotGate.h"

namespace GateDrawing
{

ref class RectangleMarker: public IGateDrawing
{
public:
    RectangleMarker();
    ~RectangleMarker();


    virtual event GateChangedHandler^ GateChanged;

    virtual void Attach(
        NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
        NationalInstruments::UI::XYPlot^ Plot);
    virtual void Detach();

    virtual IPlotGate^ GetCurrentGate();


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