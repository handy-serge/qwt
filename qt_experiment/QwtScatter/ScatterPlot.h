#pragma once
#include <QWidget>
#include <QScopedPointer>
#include <qwt_plot.h>

template <typename T>
class QList;

class QwtPlotCurve;
class QwtPlotSpectrogram;


class ScatterPlot: public QwtPlot
{
    Q_OBJECT

public:
    ScatterPlot(QWidget *parent = NULL);
    typedef QList<QwtPlotCurve*> GateShapeList;

    // keeping aspect ratio.
    virtual int heightForWidth(int width) const;
    virtual bool hasHeightForWidth() const;

private:
    QScopedPointer<GateShapeList> m_gateShapes;

    QwtPlotSpectrogram *m_spectrogram;
};

