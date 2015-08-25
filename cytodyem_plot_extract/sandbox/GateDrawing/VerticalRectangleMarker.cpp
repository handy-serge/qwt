#include "StdAfx.h"

#include "VerticalRectangleMarker.h"

#include "PlotGate.h"

#undef max
#undef min

#include <limits>

using namespace System;
using namespace System::Drawing;

namespace GateDrawing
{;


 VerticalRectangleMarker::VerticalRectangleMarker()
{
    m_ButtonDownPlot = false;
    m_CurrentGate = gcnew PlotGateRect;
	m_completeDrawing = false;
}

void  VerticalRectangleMarker::ButtonDown(
    System::Object^ sender,
    System::Windows::Forms::MouseEventArgs^ e)
{
    System::Windows::Forms::Keys k = System::Windows::Forms::Control::ModifierKeys;
    bool ModifierKeyDown = (k != System::Windows::Forms::Keys::None);
    if (!m_completeDrawing && !ModifierKeyDown)
    {
        m_ButtonDownPlot = true;
        m_Pt0.X = e->X;
        m_Pt0.Y = e->Y;
    }
}

void VerticalRectangleMarker::eraseMarker()
{
	m_Gate.X = 0;
    m_Gate.Y = 0;
    m_Gate.Width = 0;
    m_Gate.Height = 0;

    // Invalidate entire window.  Invalidating only the previous rectangle
    // cause redraw problem when the user zoom between region selection.  Invalidating
    // the entire window simplifies the handling of this case.
    m_Graph->Invalidate();
    m_Rect.X = 0;
    m_Rect.Y = 0;
    m_Rect.Width = 0;
    m_Rect.Height = 0;

    m_completeDrawing = false;
}

void  VerticalRectangleMarker::ButtonUp(
    System::Object^ sender,
    System::Windows::Forms::MouseEventArgs^ e)
{
    if (m_ButtonDownPlot)
    {
        m_ButtonDownPlot = false;
		m_completeDrawing = true;
        GateChanged();
    }
}


void  VerticalRectangleMarker::MouseMove(
    System::Object^ sender,
    System::Windows::Forms::MouseEventArgs^ e)
{
    if (m_ButtonDownPlot)
    {
        m_Pt1.X = e->X;
        m_Pt1.Y = e->Y;

        // Inflate by 2 to cover in case we have rounding discrepancies due to
        // conversion between screen coordinates and graph coordinates.
        m_Rect.Inflate(2, 2);
        m_Graph->Invalidate(m_Rect);
        m_Rect.Inflate(-2, -2);

        System::Drawing::Point ptMin(Math::Min(m_Pt0.X, m_Pt1.X),
            Math::Min(m_Pt0.Y, m_Pt1.Y));
        System::Drawing::Point ptMax(Math::Max(m_Pt0.X, m_Pt1.X),
            Math::Max(m_Pt0.Y, m_Pt1.Y));

        ptMin.X = Math::Max(ptMin.X, m_Graph->PlotAreaBounds.X);
        ptMin.Y = Math::Max(ptMin.Y, m_Graph->PlotAreaBounds.Y);
        ptMax.X = Math::Min(ptMax.X, m_Graph->PlotAreaBounds.Width + m_Graph->PlotAreaBounds.X - 1);
        ptMax.Y = Math::Min(ptMax.Y, m_Graph->PlotAreaBounds.Height + m_Graph->PlotAreaBounds.Y - 1);

        // Histogram rectangle uses the maximum bounds for Y axis.
        ptMin.Y = m_Graph->PlotAreaBounds.Y;
        ptMax.Y = m_Graph->PlotAreaBounds.Height + m_Graph->PlotAreaBounds.Y - 1;

        m_Rect.X = ptMin.X;
        m_Rect.Y = ptMin.Y;
        m_Rect.Width = ptMax.X - ptMin.X;
        m_Rect.Height = ptMax.Y - ptMin.Y;

        m_Rect.Inflate(2, 2);
        m_Graph->Invalidate(m_Rect);
        m_Rect.Inflate(-2, -2);

        System::Drawing::PointF point0((float)m_Rect.X,
            (float)m_Rect.Y + m_Rect.Height + 1);
        System::Drawing::PointF point1((float)m_Rect.X + m_Rect.Width + 1,
            (float)m_Rect.Y);
        double x0, y0;
        double x1, y1;
        m_Plot->InverseMapDataPoint(m_Graph->PlotAreaBounds, point0, x0, y0);
        m_Plot->InverseMapDataPoint(m_Graph->PlotAreaBounds, point1, x1, y1);

        // Adjust rectangle for the Y axis in histogram.
        NationalInstruments::UI::YAxis^ yaxis = m_Graph->YAxes[0];
        double MinY = yaxis->Range->Minimum;
        double MaxY = yaxis->Range->Maximum;
        y0 = MinY;
        y1 = MaxY;

        m_Gate.X = (float)x0;
        m_Gate.Y = (float)y0;
        m_Gate.Width = (float)(x1 - x0);
        m_Gate.Height = (float)(y1 - y0);
    }
}

void  VerticalRectangleMarker::BeforeDrawPlot(
    System::Object^ sender,
    NationalInstruments::UI::BeforeDrawXYPlotEventArgs^ e)
{
    Graphics^ g = e->Graphics;
    Brush^ brush = gcnew SolidBrush(Drawing::Color::FromArgb(128, 222, 191, 18)); // Yellowish Gate

    NationalInstruments::UI::XYPlot^ Plot = m_Plot;
    PointF point1 = Plot->MapDataPoint(e->Bounds, m_Gate.X, m_Gate.Y + m_Gate.Height);
    PointF point2 = Plot->MapDataPoint(e->Bounds, m_Gate.X + m_Gate.Width, m_Gate.Y);

    // Adjus Y coordinate of points for histogram.
    point1.Y = (float)m_Graph->PlotAreaBounds.Y;
    point2.Y = (float)m_Graph->PlotAreaBounds.Height + m_Graph->PlotAreaBounds.Y - 1;

    // Make sure the box is always visible.
    point2.X = Math::Max(point2.X, point1.X + 2.0f);
    point2.Y = Math::Max(point2.Y, point1.Y + 2.0f);

    //g->DrawRectangle(Drawing::Pens::Blue, point1.X, point1.Y, point2.X - point1.X - 1, point2.Y - point1.Y - 1);
    g->FillRectangle(brush, point1.X, point1.Y, point2.X - point1.X - 1, point2.Y - point1.Y - 1);
    //g->DrawString("GateNameHere", gcnew Font("Arial", 10), gcnew SolidBrush(Drawing::Color::Black), point1);
    //g->DrawRectangle(Drawing::Pens::Blue, point1.X, point1.Y, point2.X - point1.X - 1, point2.Y - point1.Y - 1);
}


void  VerticalRectangleMarker::Attach(
    NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
    NationalInstruments::UI::XYPlot^ Plot)
{
    m_Graph = Graph;
    m_Plot = Plot;

    Graph->BeforeDrawPlot += gcnew NationalInstruments::UI::BeforeDrawXYPlotEventHandler(this, & VerticalRectangleMarker::BeforeDrawPlot);

    //Graph->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PlotGateHandler::scatterGraph1_MouseDown);
    Graph->PlotAreaMouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, & VerticalRectangleMarker::ButtonDown);

    Graph->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, & VerticalRectangleMarker::MouseMove);
    // Graph->PlotAreaMouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PlotGateHandler::scatterGraph1_PlotAreaMouseMove);

    Graph->PlotAreaMouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, & VerticalRectangleMarker::ButtonUp);
    Graph->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, & VerticalRectangleMarker::ButtonUp);
}


IPlotGate^  VerticalRectangleMarker::GetCurrentGate()
{
    if (m_Gate.Width != 0 || m_Gate.Height != 0)
    {
        m_CurrentGate->SetRect(m_Gate.X, m_Gate.Y, m_Gate.X + m_Gate.Width, m_Gate.Y + m_Gate.Height);
    }
    else
    {

        m_CurrentGate->SetRect(-std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max());
    }
    return m_CurrentGate;
}

VerticalRectangleMarker::~VerticalRectangleMarker()
{
    Detach();
}

void VerticalRectangleMarker::Detach()
{
    if (m_Graph)
    {
		eraseMarker();

        m_Graph->BeforeDrawPlot -= gcnew NationalInstruments::UI::BeforeDrawXYPlotEventHandler(this, &VerticalRectangleMarker::BeforeDrawPlot);

        //Graph->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PlotGateHandler::scatterGraph1_MouseDown);
        m_Graph->PlotAreaMouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &VerticalRectangleMarker::ButtonDown);

        m_Graph->MouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &VerticalRectangleMarker::MouseMove);
        // Graph->PlotAreaMouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &PlotGateHandler::scatterGraph1_PlotAreaMouseMove);

        m_Graph->PlotAreaMouseUp -= gcnew System::Windows::Forms::MouseEventHandler(this, &VerticalRectangleMarker::ButtonUp);
        m_Graph->MouseUp -= gcnew System::Windows::Forms::MouseEventHandler(this, &VerticalRectangleMarker::ButtonUp);
    }

    m_Graph = nullptr;
    m_Plot = nullptr;
}


} // namespace GateDrawing.