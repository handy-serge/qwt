import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtWinExtras 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello QML")

    signal menuClicked(string text)

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                shortcut: "Ctrl+Q"
                onTriggered: Qt.quit()
            }
            MenuItem {
                text: qsTr("Click me!")
                onTriggered: window.menuClicked(text)
            }
        }
    }

    Text {
        id: hw
        text: qsTr("Hello World")
        font.capitalization: Font.AllUppercase
        anchors.centerIn: parent
    }

    Label {
        anchors { bottom: hw.top; bottomMargin: 5; horizontalCenter: hw.horizontalCenter }
        text: qsTr("Hello Qt Quick")
    }
}
