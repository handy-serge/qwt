#include "QwtScatter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QwtScatter w;
    w.show();
    return a.exec();
}
