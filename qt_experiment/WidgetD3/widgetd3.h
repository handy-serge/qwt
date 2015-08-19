#ifndef WIDGETD3_H
#define WIDGETD3_H

#include <QtWidgets/QMainWindow>
#include "ui_widgetd3.h"

class WidgetD3 : public QMainWindow
{
	Q_OBJECT

public:
	WidgetD3(QWidget *parent = 0);
	~WidgetD3();

private:
	Ui::WidgetD3Class ui;
};

#endif // WIDGETD3_H
