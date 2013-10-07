#pragma once

#using "Interfaces.dll"
#using "System.Windows.Forms.dll"
#using "System.Drawing.dll"

#include "PlotGate.h"

namespace GateDrawing
{

    ref class PolygonMarker: public IGateDrawing
    {
    public:
        PolygonMarker();
        ~PolygonMarker();


        virtual event GateChangedHandler^ GateChanged;

        virtual void Attach(
            NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
            NationalInstruments::UI::XYPlot^ Plot);
        virtual void Detach();

        virtual IPlotGate^ GetCurrentGate();


    private:
        void HandleMouseClick(
            System::Object^ sender,
            System::Windows::Forms::MouseEventArgs^ e);

        void HandleDoubleClick(
            System::Object^ sender,
            System::Windows::Forms::MouseEventArgs^ e);

        void HandleMouseMove(
            System::Object^ sender,
            System::Windows::Forms::MouseEventArgs^ e);

        void BeforeDrawPlot(
            System::Object^ sender,
            NationalInstruments::UI::BeforeDrawXYPlotEventArgs^ e);


        NationalInstruments::UI::WindowsForms::XYGraph^ m_Graph;
        NationalInstruments::UI::XYPlot ^m_Plot;

        // Polygon points in as a data coordinates.
        System::Collections::Generic::List<System::Drawing::PointF> ^m_points;

        bool m_isDrawing;
    };
};