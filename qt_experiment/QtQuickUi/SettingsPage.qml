import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Tab {
    title: 'Settings'

    GridLayout{
        rows: 3
        columns: 4

        anchors.fill: parent

        // Load button:
        Image {
            Layout.columnSpan: 4
            source: 'images/settings-load-button.png'
        }

        // Loaded file info:
        TabView {
            Layout.alignment:  Qt.AlignTop
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 2

            Tab {
                title: 'File'
                Image {
                    source: 'images/settings-loaded-file.png'
                    fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignTop
                }
            }
            Tab {
                title: 'Experiment'
                Image {
                    source: 'images/settings-loaded-experiment.png'
                    fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignTop
                }
            }
            Tab {
                title: 'Fluidics'
                Image {
                    source: 'images/settings-loaded-fluidics.png'
                    fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignTop
                }
            }
        }

        ColumnLayout {
            Layout.rowSpan: 2
            Layout.alignment:  Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Current file info:
            Image {
                Layout.fillWidth: true
                Layout.alignment:  Qt.AlignHCenter | Qt.AlignTop
                source: 'images/settings-current-file.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }

            // Current instrument info
            Image {
                Layout.fillWidth: true
                Layout.alignment:  Qt.AlignHCenter | Qt.AlignBottom
                source: 'images/settings-current-instrument.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }
        }
        // Current experiment info:
        Image {
            Layout.alignment:  Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            Layout.rowSpan: 2
            source: 'images/settings-current-experiment.png'
            fillMode: Image.PreserveAspectFit
            verticalAlignment: Image.AlignTop
        }

        // Fluidics procedures:
        Image {
            Layout.alignment:  Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            source: 'images/settings-fluidics-operation.png'
            fillMode: Image.PreserveAspectFit
            verticalAlignment: Image.AlignTop
        }

        // Save button:
        Image {
            source: 'images/settings-save-buttons.png'
            Layout.alignment:  Qt.AlignTop | Qt.AlignRight
        }
    }
}
