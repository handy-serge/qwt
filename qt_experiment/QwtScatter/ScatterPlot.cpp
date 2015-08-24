#include "ScatterPlot.h"
#include "GateShapes.h"

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
