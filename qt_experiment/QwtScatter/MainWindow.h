#ifndef QWTSCATTER_H
#define QWTSCATTER_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class ScatterPlot;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow ui;
    ScatterPlot *m_plot;

};

#endif // QWTSCATTER_H
