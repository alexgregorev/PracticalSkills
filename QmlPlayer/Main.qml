import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Rectangle {
                color: "navajowhite";
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    text: "Qml Player"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 24; font.bold: true
                }
            }

            RowLayout {
                Rectangle {
                    color: 'lightgray'
                    Layout.maximumHeight: 70
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                GridLayout {
                   rows: 2
                   columns: 6
                    Rectangle {
                        implicitWidth: 120
                        implicitHeight: 30

                        Button {
                            text: "         ▶️         "
                            font.pointSize: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Rectangle {
                        implicitWidth: 120
                        implicitHeight: 30

                        Button {
                            text: "         ⏸️         "
                            font.pointSize: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Rectangle {
                        implicitWidth: 120
                        implicitHeight: 30

                        Button {
                            text: "         ⏹         "
                            font.pointSize: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Rectangle {
                        implicitWidth: 120
                        implicitHeight: 30

                        Button {
                            text: "         ⏪️         "
                            font.pointSize: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Rectangle {
                        implicitWidth: 120
                        implicitHeight: 30

                        Button {
                            text: "         ⏩️         "
                            font.pointSize: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Rectangle {
                        implicitWidth: 630
                        implicitHeight: 30
                        Layout.columnSpan: 5
                        Layout.alignment: Qt.AlignHCenter

                        ProgressBar {
                            implicitWidth: 630
                            implicitHeight: 30

                            Slider {
                                implicitWidth: 630
                                implicitHeight: 30
                            }
                        }
                    }
                }

                Rectangle {
                    color: 'lightgray'
                    Layout.maximumHeight: 70
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}
