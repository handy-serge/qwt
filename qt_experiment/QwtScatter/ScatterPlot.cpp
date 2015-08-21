#include "ScatterPlot.h"

#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>

// Changes widget background to make visible the place it takes on a screen.
void HighlightWidget(QWidget *widget, QColor const& color)
{
    widget->setAutoFillBackground(true);
    auto colors = widget->palette();
    colors.setColor(widget->backgroundRole(), color);
    widget->setPalette(colors);
    widget->setMinimumSize(200, 600);
    widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}


QPolygonF const PAC_MAN = []()
{
    QPolygonF points;
    points 
        << QPointF(30, 50)
        << QPointF(40, 70)
        << QPointF(60, 70)
        << QPointF(70, 60)
        << QPointF(50, 50)
        << QPointF(70, 40)
        << QPointF(60, 30)
        << QPointF(40, 30)
        << QPointF(30, 50)
        ;
    return points;
}();

// Yes, pac-man enemies had names.
QPolygonF const OIKAKE = []()
{
    QPolygonF points;
    points
        << QPointF(20, 20)
        << QPointF(30, 40)
        << QPointF(40, 50)
        << QPointF(50, 50)
        << QPointF(60, 50)
        << QPointF(70, 40)
        << QPointF(80, 20)
        << QPointF(70, 10)
        << QPointF(60, 20)
        << QPointF(50, 10)
        << QPointF(40, 20)
        << QPointF(30, 10)
        << QPointF(20, 20)
        ;
    return points;
}();


QwtPlot* setupPlot(QwtPlot *plot)
{
    plot->setTitle("Scatter plot");
    plot->setCanvasBackground(Qt::white);
    plot->insertLegend(new QwtLegend());

    plot->setAxisScale(QwtPlot::xBottom, 0, 100.0);
    plot->setAxisScale(QwtPlot::yLeft, 0, 100.0);
    auto grid = new QwtPlotGrid();
    grid->attach(plot);
    return plot;
}


QwtPlotCurve* setupGateShape(
    QwtPlotCurve *curve
    , QPolygonF const& points
    , QColor const& color
    , QString const& title)
{
    curve->setSamples(points);
    curve->setTitle(title);
    curve->setPen(color, 3);

    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    return curve;
}

ScatterPlot::GateShapeList *setupGateShapes(
    ScatterPlot::GateShapeList *gateShapes
    , QwtPlot *plot
    )
{
    auto makeShape = [](){return new QwtPlotCurve();};
    *gateShapes 
        << setupGateShape(makeShape(), OIKAKE, Qt::red, "Oikake")
        << setupGateShape(makeShape(), PAC_MAN, Qt::blue, "Pac-man")
        ;
    for (auto shape: *gateShapes)
    {
        shape->attach(plot);
    }
    return gateShapes;
}

ScatterPlot::ScatterPlot( QWidget* parent)
    : QwtPlot(parent)
    , m_gateShapes(new GateShapeList())
{
    // Changing background color and size of the widget to see if
    // it is correctly added to layout (for debugging layouts).  
    // HighlightWidget(this, Qt::darkGray);

    setupPlot(this);
    setupGateShapes(m_gateShapes.data(), this);
}
