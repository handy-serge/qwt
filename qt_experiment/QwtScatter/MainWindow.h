#ifndef QWTSCATTER_H
#define QWTSCATTER_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::QwtScatterClass ui;
};

#endif // QWTSCATTER_H
