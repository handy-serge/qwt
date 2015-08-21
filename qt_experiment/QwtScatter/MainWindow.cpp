#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Setup connect to ui signals.
    connect(ui.exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{

}

