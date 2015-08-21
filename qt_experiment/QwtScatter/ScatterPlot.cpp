#include "ScatterPlot.h"

ScatterPlot::ScatterPlot( QWidget* parent)
    : QWidget(parent)
{
    // Changing background color and size of the widget to see if
    // it is correctly added to layout.
    setAutoFillBackground(true);
    auto colors = palette();
    colors.setColor(backgroundRole(), Qt::darkGray);
    setPalette(colors);
    setMinimumSize(200, 600);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}
