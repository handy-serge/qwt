#include "StdAfx.h"

#include "PolygonMarker.h"

#include "PlotGate.h"

#undef max
#undef min

#include <limits>

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace GateDrawing
{;

PolygonMarker::PolygonMarker()
{
    m_points = gcnew List<System::Drawing::PointF>();
    m_isDrawing = false;
	m_completeDrawing = false;
}

// If number is smaller than minimum or bigger than maximum, it is set to a minimum or maximum,
// otherwise it is left unchanged.
int PutIntegerIntoTheRange(int number, int minimum, int maximum)
{
    int rangedNumber = number;
    if (number > maximum)
    {
        rangedNumber = maximum;
    }
    else if (number < minimum)
    {
        rangedNumber = minimum;
    }
    return rangedNumber;
}



Point FitPointInsideGraphBounds(
    Point point,
    NationalInstruments::UI::WindowsForms::XYGraph^ graph
    )
{
    int const x = PutIntegerIntoTheRange(point.X,
        graph->PlotAreaBounds.X,
        graph->PlotAreaBounds.X + graph->PlotAreaBounds.Width);

    int const y = PutIntegerIntoTheRange(point.Y,
        graph->PlotAreaBounds.Y
        , graph->PlotAreaBounds.Y + graph->PlotAreaBounds.Height);

    Point const result(x, y);
    return result;
}

// Gets the point in a screen coordinates and returns corresponding point in data coordinates.
PointF FromScreenToData(
    Point point,
    NationalInstruments::UI::WindowsForms::XYGraph^ graph,
    NationalInstruments::UI::XYPlot^ plot
    )
{
    Point pointWithinBounds = FitPointInsideGraphBounds(point, graph);
    PointF const screenPoint = PointF( (float)pointWithinBounds.X, (float)pointWithinBounds.Y);

    double x;
    double y;
    plot->InverseMapDataPoint(graph->PlotAreaBounds,
        screenPoint,
        x, y);

    PointF const result((float)x, (float)y);
    return result;
}

void PolygonMarker::HandleMouseClick(
    System::Object^ sender,
    System::Windows::Forms::MouseEventArgs^ e)
{
    System::Windows::Forms::Keys k = System::Windows::Forms::Control::ModifierKeys;
    bool ModifierKeyDown = (k != System::Windows::Forms::Keys::None);
    if (!ModifierKeyDown && !m_completeDrawing)
    {
		System::Drawing::Point const screenPoint(e->X, e->Y);
		System::Drawing::PointF const dataPoint = FromScreenToData(screenPoint, m_Graph, m_Plot);
		m_Graph->Invalidate();

		m_points->Add(dataPoint);
		

        m_isDrawing = true;
        
    }
}

void PolygonMarker::eraseMarker()
{
    if (!m_isDrawing)
    {
        // Remove all points.
        m_points->Clear();
		m_Graph->Invalidate();
    }

    m_completeDrawing = false;
}

void PolygonMarker::HandleDoubleClick(
    System::Object^ sender,
    System::Windows::Forms::MouseEventArgs^ e)
{
    m_isDrawing = false;
	m_completeDrawing = true;
}


void PolygonMarker::HandleMouseMove(
    System::Object^ sender,
    System::Windows::Forms::MouseEventArgs^ e)
{
    if (!m_isDrawing || m_completeDrawing)
    {
        return;
    }

    System::Drawing::Point const screenPoint(e->X, e->Y);
    System::Drawing::PointF const dataPoint = FromScreenToData(screenPoint, m_Graph, m_Plot);

    if (m_points->Count)
    {
        m_points->RemoveAt(m_points->Count - 1);
    }
    m_points->Add(dataPoint);
    m_Graph->Invalidate();
}

void PolygonMarker::BeforeDrawPlot(
    System::Object^ sender,
    NationalInstruments::UI::BeforeDrawXYPlotEventArgs^ e)
{
    Graphics^ g = e->Graphics;
    Brush^ brush = gcnew SolidBrush(Drawing::Color::FromArgb(128, 222, 191, 18)); // Yellowish Gate

    array<PointF>^ points = gcnew array<PointF>(m_points->Count);
    int i = 0;
    for each(PointF point in m_points)
    {
        PointF screenPoint  = m_Plot->MapDataPoint(e->Bounds, point.X, point.Y);
        points[i++] = screenPoint;
    }
    if (points->Length)
    {
        g->FillPolygon(brush, points);
    }
}


void PolygonMarker::Attach(
    NationalInstruments::UI::WindowsForms::XYGraph^ Graph,
    NationalInstruments::UI::XYPlot^ Plot)
{
    m_Graph = Graph;
    m_Plot = Plot;

    Graph->BeforeDrawPlot += gcnew NationalInstruments::UI::BeforeDrawXYPlotEventHandler(this, &PolygonMarker::BeforeDrawPlot);

    m_Graph->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &PolygonMarker::HandleMouseClick);

    m_Graph->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PolygonMarker::HandleMouseMove);
    m_Graph->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &PolygonMarker::HandleDoubleClick);
}

PolygonMarker::~PolygonMarker()
{
    Detach();
}


IPlotGate^ PolygonMarker::GetCurrentGate()
{
    return nullptr;
}

void PolygonMarker::Detach()
{
    if (m_Graph)
    {
		// Delete current gate
		eraseMarker();

        m_Graph->BeforeDrawPlot -= gcnew NationalInstruments::UI::BeforeDrawXYPlotEventHandler(this, &PolygonMarker::BeforeDrawPlot);

        m_Graph->MouseClick -= gcnew System::Windows::Forms::MouseEventHandler(this, &PolygonMarker::HandleMouseClick);
        m_Graph->MouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &PolygonMarker::HandleMouseMove);
        m_Graph->MouseDoubleClick -= gcnew System::Windows::Forms::MouseEventHandler(this, &PolygonMarker::HandleDoubleClick);
    }
    m_Graph = nullptr;
    m_Plot = nullptr;
}


} // namespace GateDrawing



