import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit()
            }
        }
    }
