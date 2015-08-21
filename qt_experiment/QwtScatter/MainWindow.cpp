#include "MainWindow.h"
#include "ScatterPlot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_plot(new ScatterPlot(this))
{
    ui.setupUi(this);

    // Add plot to the main window at the top of the plot layout.
    ui.plotAreaLayout->insertWidget(0, m_plot);

    // Setup connect to ui signals.
    connect(ui.exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{

}

