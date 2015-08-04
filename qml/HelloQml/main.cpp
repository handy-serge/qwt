#include <QApplication>
#include <QQmlApplicationEngine>

#include "processor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().first();

    Processor processor;
    QObject::connect(
                root, SIGNAL(menuClicked(QString)),
                &processor, SLOT(onMenuClicked(QString)));

    return app.exec();
}
