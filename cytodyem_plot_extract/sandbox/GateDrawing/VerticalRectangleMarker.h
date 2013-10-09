#pragma once
#using "Interfaces.dll"

namespace GateDrawing
{;
ref class PlotGateRect;
ref class VerticalRectangleMarker: public IGateDrawing
{
public:
    VerticalRectangleMarker();
    ~VerticalRectangleMarker();

    virtual event GateChangedHandler^ GateChanged;
    virtual void Attach(
        NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
        NationalInstruments::UI::XYPlot^ Plot);

    virtual void Detach();

    virtual void eraseMarker();

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
	bool m_completeDrawing;
    System::Drawing::Point m_Pt0;
    System::Drawing::Point m_Pt1;
};

}