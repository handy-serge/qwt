#include "ScatterPlot.h"
#include "GateShapes.h"
#include "RasterData.h"

#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_layout.h>
#include <qwt_color_map.h>

#include <qwt_plot_canvas.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_glcanvas.h>


// Changes widget background to make visible the place it takes on a screen.
void HighlightWidget(QWidget *widget, QColor const& color)
{
    widget->setAutoFillBackground(true);
    auto colors = widget->palette();
    colors.setColor(widget->backgroundRole(), color);
    widget->setPalette(colors);
    widget->setMinimumSize(200, 200);
    widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

QwtPlot* setupPlot(QwtPlot *plot)
{
    plot->setMinimumSize(300, 300);
    plot->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

// Two lines below enable OpenGL rendering.
    auto canvas = new QwtPlotGLCanvas();
    plot->setCanvas(canvas);

    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(plot->canvas() );
    QwtPlotPanner *panner = new QwtPlotPanner(plot->canvas());
    panner->setMouseButton(Qt::MidButton);

    QwtPlotZoomer *zoomer = new QwtPlotZoomer(plot->canvas());

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


class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::white, Qt::darkRed )
    {
        addColorStop( 0.2, Qt::lightGray );
        addColorStop( 0.4, Qt::cyan);
        addColorStop( 0.6, Qt::yellow );
        addColorStop( 0.8, Qt::darkYellow );
    }
};


QwtPlotSpectrogram* setupSpectrogram(
    QwtPlotSpectrogram *spectrogram
    , QwtPlot *plot
    )
{
    spectrogram->setCachePolicy(QwtPlotRasterItem::PaintCache);
    auto data = new RasterData();
//    data->setResampleMode(QwtMatrixRasterData::BilinearInterpolation);
    data->setResampleMode(QwtMatrixRasterData::NearestNeighbour);

    spectrogram->setData(data);
    spectrogram->setColorMap(new ColorMap());
    spectrogram->attach(plot);
    spectrogram->setRenderThreadCount(4);

    plot->plotLayout()->setAlignCanvasToScales( true );

    plot->setAxisScale(QwtPlot::xBottom, 0, data->interval(Qt::XAxis).maxValue());
    plot->setAxisScale(QwtPlot::yLeft, 0, data->interval(Qt::YAxis).maxValue());

    return spectrogram;
}


ScatterPlot::ScatterPlot( QWidget* parent)
    : QwtPlot(parent)
    , m_gateShapes(new GateShapeList())
    , m_spectrogram(new QwtPlotSpectrogram())
{
    // Changing background color and size of the widget to see if
    // it is correctly added to layout (for debugging layouts).  
    // HighlightWidget(this, Qt::darkGray);

    setupPlot(this);
    setupGateShapes(m_gateShapes.data(), this);
    setupSpectrogram(m_spectrogram, this);
}

int ScatterPlot::heightForWidth( int width ) const
{
    return width;

}

bool ScatterPlot::hasHeightForWidth() const
{
    return true;
}
