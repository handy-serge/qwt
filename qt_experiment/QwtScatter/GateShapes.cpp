#include "GateShapes.h"

#include <qwt_plot_curve.h>

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

// Pac-man enemies had names. 
// See: https://en.wikipedia.org/wiki/Pac-Man
// Oikake (chaser), aka Shadow / Blinky
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
