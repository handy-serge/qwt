import QtQuick 2.4

Rectangle {
    readonly property color defaultColor: '#afdff0'
    readonly property color clickedColor: 'green'

    color: defaultColor


    focus: true
    Keys.onSpacePressed:  {
        color = defaultColor
    }
    MouseArea{
        onClicked: { parent.color = parent.clickedColor}
        anchors.fill: parent
    }
}

