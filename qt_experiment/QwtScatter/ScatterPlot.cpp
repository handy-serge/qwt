#include "ScatterPlot.h"

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

ScatterPlot::ScatterPlot( QWidget* parent)
    : QwtPlot(parent)
{
    // Changing background color and size of the widget to see if
    // it is correctly added to layout.
    HighlightWidget(this, Qt::darkGray);
}
