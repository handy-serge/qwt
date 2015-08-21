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


QwtPlotCurve* setupGateShape(QwtPlotCurve *curve)
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

    curve->setSamples(points);
    curve->setTitle("Gate 1");
    curve->setPen(Qt::blue, 3);

    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    return curve;
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

ScatterPlot::ScatterPlot( QWidget* parent)
    : QwtPlot(parent)
    , m_gateShape(new QwtPlotCurve())
{
    // Changing background color and size of the widget to see if
    // it is correctly added to layout (for debugging layouts).  
    // HighlightWidget(this, Qt::darkGray);

    setupPlot(this);
    setupGateShape(m_gateShape);
    m_gateShape->attach(this);
}
