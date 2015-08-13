import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import '.' as Style

TabViewStyle {
    frameOverlap: 1
    tabBar: Rectangle {
        color: Style.Colors.handyRed
    }

    tab: Rectangle {
            anchors.topMargin: 5
            id: outer
            color: styleData.selected
                   ? Style.Colors.handyWhite
                   : Style.Colors.whitish
            border.color:  Style.Colors.handyRed

            implicitWidth: Math.max(text.width + 4, 80)
            implicitHeight: 26

            Rectangle {
                id: rounding
                color: Style.Colors.handyWhite
                radius: 8
                width: parent.width
                height: radius
                anchors.top: parent.top
            }
            Rectangle {
                gradient: Gradient {
                    GradientStop {position: 0; color: Style.Colors.handyWhite}
                    GradientStop {position: 1; color: outer.color}
                }
                color: outer.color
                anchors.bottom: parent.bottom
                anchors.topMargin: rounding.height / 2
                width: parent.width
                height: parent.height - rounding.height / 2
                Label {
                    id: text
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: - rounding.radius / 4
                    text: styleData.title
                    font.bold: styleData.selected
                    font.pointSize: 11
                    color: styleData.selected
                           ? Style.Colors.handyRed : Style.Colors.handyBlue
                }
            }
        }
    tabOverlap: -2
    frame: Rectangle {
        color: Style.Colors.handyWhite
    }
}
