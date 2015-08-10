import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import "." as Gui

ApplicationWindow {
    title: qsTr("Quick GUI prototype")
    width: 800
    height: 600

    menuBar: Gui.ApplicationMenu {}

    Gui.ApplicationWindow {
        anchors.fill: parent
    }
}

