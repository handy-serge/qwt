#pragma once
#include <QWidget>
#include <qwt_plot.h>

class QwtPlotCurve;
class ScatterPlot: public QwtPlot
{
    Q_OBJECT

public:
    ScatterPlot(QWidget *parent = NULL);

private:
    QwtPlotCurve *m_gateShape;

};

