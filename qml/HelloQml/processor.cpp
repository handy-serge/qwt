#include "processor.h"

#include <QDebug>

Processor::Processor(QObject *parent) : QObject(parent)
{

}

void Processor::onMenuClicked(const QString &text)
{
    qDebug() << text;
}

