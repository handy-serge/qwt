#pragma once

class QwtPlotCurve;

class QPolygonF;
class QColor;
class QString;

QwtPlotCurve* setupGateShape(
    QwtPlotCurve *curve
    , QPolygonF const& points
    , QColor const& color
    , QString const& title);

extern QPolygonF const PAC_MAN;
extern QPolygonF const OIKAKE;
