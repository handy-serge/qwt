#pragma once
#include <QWidget>
#include <QScopedPointer>
#include <qwt_plot.h>

template <typename T>
class QList;

class QwtPlotCurve;
class ScatterPlot: public QwtPlot
{
    Q_OBJECT

public:
    ScatterPlot(QWidget *parent = NULL);

    typedef QList<QwtPlotCurve*> GateShapeList;

private:
    QScopedPointer<GateShapeList> m_gateShapes;
};

