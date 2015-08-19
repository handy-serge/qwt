// The source code is adopted from this article:
// http://habrahabr.ru/post/218389/


#include <QApplication>
#include "charts/pie/dependencywheelwidget.h"
#include <QDebug>
#include <QTextCodec>

void setDependencies(d3widgets::DependencyWheelWidget *wheelWidget);

int main(int argc, char *argv[])
{

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForCStrings (QTextCodec::codecForName("utf-8"));
#endif

    QApplication a(argc, argv);

    for (int i = 0; i < 1 ; i++) // for memory usage testing
    {
    d3widgets::DependencyWheelWidget *dependencyWheelWidget = new d3widgets::DependencyWheelWidget();
    setDependencies(dependencyWheelWidget);
    dependencyWheelWidget->setMargin(200);
    dependencyWheelWidget->show();
    }
    return a.exec();
}

void setDependencies(d3widgets::DependencyWheelWidget *wheelWidget)
{
    // Setup dependencies, for example the hub "Programming" может can include
	// article from hub "Python"
    wheelWidget->appendDependency("Programming", "Python");
    wheelWidget->appendDependency("Programming", "C++");
    wheelWidget->appendDependency("Programming", "Web development");
    wheelWidget->appendDependency("Programming", "PHP");
    wheelWidget->appendDependency("Programming", "JavaScript");
    wheelWidget->appendDependency("Programming", "Java");
    wheelWidget->appendDependency("Web development", "CSS");
    wheelWidget->appendDependency("Web development", "PHP");
    wheelWidget->appendDependency("Web development", "HTML");
    wheelWidget->appendDependency("Web development", "Web design");
    wheelWidget->appendDependency("Web development", "JavaScript");
    wheelWidget->appendDependency("JavaScript", "Web development");
    wheelWidget->appendDependency("Python", "Web development");
    wheelWidget->appendDependency("Game-development", "Java");
    wheelWidget->appendDependency("Game-development", "Mobile Development");
    wheelWidget->appendDependency("Information security", "Cryptography");
    wheelWidget->appendDependency("Cryptography", "Algorithms");
    wheelWidget->appendDependency("Development", "Web development");
    wheelWidget->appendDependency("Development", "Game-development");
    wheelWidget->appendDependency("Development", "Mobile Development");
    wheelWidget->appendDependency("Development", "Development for Windows");
    wheelWidget->appendDependency("Development", "Microcontrollers programming");
    wheelWidget->appendDependency("Microcontrollers programming", "FPGA");
    wheelWidget->appendDependency("FPGA", "Microcontrollers programming");
    wheelWidget->appendDependency("Microcontrollers programming", "Assembler");
    wheelWidget->appendDependency("Microcontrollers programming", "Electronics for beginners");
    wheelWidget->appendDependency("Electronics for beginners", "FPGA");
    wheelWidget->appendDependency("OpenSource", "Programming");
    wheelWidget->appendDependency("OpenSource", "Programming");
    wheelWidget->appendDependency("C++", "Programming");
    wheelWidget->appendDependency("Interfaces", "Data visualisation");
    wheelWidget->appendDependency("Web design", "Data visualisation");
    wheelWidget->appendDependency("Web design", "Usability");
    wheelWidget->appendDependency("Usability", "Data visualisation");
    wheelWidget->appendDependency("Algorithms", "Programming");
    wheelWidget->appendDependency("Mobile Web", "HTML");
    wheelWidget->appendDependency("Mobile Web", "JavaScript");
    wheelWidget->appendDependency("Mobile Web", "CSS");
    wheelWidget->appendDependency("Mobile Development", "Development for Android");
    wheelWidget->appendDependency("Mobile Development", "Development for iOS");
    wheelWidget->appendDependency("Mobile Development", "Development for Windows Phone");
    wheelWidget->appendDependency("Mobile Development", "Mobile Web");
    wheelWidget->appendDependency("Mobile Development", "C#");
    wheelWidget->appendDependency("Development for Android", "Mobile Development");
    wheelWidget->appendDependency("CSS", "Web development");
    wheelWidget->appendDependency("PHP", "Web development");
    wheelWidget->appendDependency("Python", "Web development");
    wheelWidget->appendDependency("HTML", "Web development");
    wheelWidget->appendDependency("Linux configuration", "*nix");
    wheelWidget->appendDependency("Java", "Programming");
    wheelWidget->appendDependency("C#", "Programming");
    wheelWidget->appendDependency("Development for iOS", "Mobile Development");
    wheelWidget->appendDependency("Development for Windows", "VisualStudio");
    wheelWidget->appendDependency("*nix", "Linux configuration");
    wheelWidget->appendDependency("VisualStudio", "Development for Windows");
}
