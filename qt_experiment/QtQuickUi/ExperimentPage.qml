import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Tab {
    title: 'Analysis'

    GridLayout {
        columns: 2
        anchors.fill: parent

        // Device status
        RowLayout {
            Layout.columnSpan: 2
            Layout.fillWidth: true

            Image {
                Layout.alignment:  Qt.AlignTop
                Layout.fillWidth: true
                source: 'images/analysis-operation-progress.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }
            Image {
                Layout.fillWidth: true
                Layout.alignment:  Qt.AlignTop
                source: 'images/analysis-device-messages.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }
            Image {
                Layout.fillWidth: true
                Layout.alignment:  Qt.AlignTop | Qt.AlignLeft
                source: 'images/analysis-fluidic-operations.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
                horizontalAlignment: Image.AlignLeft
            }
            Image {
                Layout.fillWidth: true
                Layout.alignment:  Qt.AlignTop | Qt.AlignRight
                source: 'images/analysis-instrument-status.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
                horizontalAlignment: Image.AlignRight
            }

        }

        // Displayed events and triggers
        ColumnLayout {
            Layout.alignment:  Qt.AlignHCenter | Qt.AlignTop
            Layout.margins: 20

            Image {
                Layout.alignment:  Qt.AlignTop
                source: 'images/analysis-displayed-events.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }
            Image {
                Layout.alignment:  Qt.AlignTop
                source: 'images/analysis-triggers-form.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }
            Image {
                id: slider
                Layout.alignment:  Qt.AlignTop
                source: 'images/analysis-trigger-slider.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
            }
            Image {
                anchors.bottom: slider.bottom
                anchors.leftMargin: 10
                opacity: 0.5
                Layout.alignment:  Qt.AlignTop
                source: 'images/handyem-logo.png'
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignTop
                horizontalAlignment: Image.AlignHCenter
            }
        }

        // Right side is resizable
        SplitView {
            // anchors.fill: parent
            orientation: Qt.Horizontal
            Layout.fillHeight: true
            Layout.fillWidth: true

            // Plots
            GridLayout
            {
                columns: 3
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                Layout.fillHeight: true
                Layout.fillWidth: true

                Image {
                    Layout.alignment:  Qt.AlignTop
                    Layout.columnSpan: 3
                    Layout.fillWidth: true
                    source: 'images/analysis-file-operations.png'
                    fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignTop
                }


                Repeater {
                    model: 9
                    Layout.columnSpan: 3
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Rectangle
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: 'white'
                        Image {
                            anchors.fill:parent
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment:  Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.minimumWidth: 15
                            Layout.minimumHeight: 15


                            source: 'images/analysis-plot-scatter.png'
                            fillMode: Image.PreserveAspectFit
                            verticalAlignment: Image.AlignTop
                            horizontalAlignment: Image.AlignHCenter
                        }

                    }

                }

            }

            // Information pane on right:
            ColumnLayout {
                Layout.alignment:  Qt.AlignHCenter | Qt.AlignTop
                Layout.margins: 3

                // Operations and count
                RowLayout {
                    Image {
                        id: terminate
                        Layout.alignment:  Qt.AlignTop
                        source: 'images/analysis-terminate-refresh.png'
                        fillMode: Image.PreserveAspectFit
                        verticalAlignment: Image.AlignTop
                    }
                    Image {
                        anchors.left: terminate.right
                        anchors.top: terminate.top
                        Layout.alignment:  Qt.AlignTop
                        source: 'images/analysis-time-vol-count.png'
                        fillMode: Image.PreserveAspectFit
                        verticalAlignment: Image.AlignTop
                    }
                }
                // Compensations and PMT
                TabView {
                    Layout.alignment:  Qt.AlignTop
                    Layout.fillWidth: true

                    Tab {
                        anchors.margins: 4
                        title: "Compensations"
                        Image {
                            Layout.alignment:  Qt.AlignTop
                            source: 'images/analysis-compensations.png'
                            fillMode: Image.PreserveAspectFit
                            verticalAlignment: Image.AlignTop
                        }
                    }
                    Tab {
                        anchors.margins: 4
                        title: "PMT Voltages"
                        Image {
                            Layout.alignment:  Qt.AlignTop
                            source: 'images/analysis-pmt-voltages.png'
                            fillMode: Image.PreserveAspectFit
                            verticalAlignment: Image.AlignTop
                        }
                    }
                }

                // Counts and stats.
                TabView {
                    Layout.alignment:  Qt.AlignTop
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Tab {
                        anchors.margins: 4
                        title: "Counts"
                        Image {
                            Layout.alignment:  Qt.AlignTop
                            source: 'images/analysis-counts.png'
                            fillMode: Image.PreserveAspectFit
                            verticalAlignment: Image.AlignTop
                        }
                    }
                    Tab {
                        anchors.margins: 4
                        title: "Stats"
                        Image {
                            Layout.alignment:  Qt.AlignTop
                            source: 'images/analysis-stats.png'
                            fillMode: Image.PreserveAspectFit
                            verticalAlignment: Image.AlignTop
                        }
                    }
                }

            }
        }
    }
}


