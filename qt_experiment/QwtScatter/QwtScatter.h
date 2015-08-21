#ifndef QWTSCATTER_H
#define QWTSCATTER_H

#include <QtWidgets/QMainWindow>
#include "ui_QwtScatter.h"

class QwtScatter : public QMainWindow
{
    Q_OBJECT

public:
    QwtScatter(QWidget *parent = 0);
    ~QwtScatter();

private:
    Ui::QwtScatterClass ui;
};

#endif // QWTSCATTER_H
