import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    property alias mouseArea: mouseArea

    width: 640
    height: 480
    property alias tableView: tableView

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        Button {
            id: start
            x: 532
            y: 432
            width: 100
            height: 40
            text: qsTr("Start")
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }

        Button {
            id: stop
            x: 426
            y: 432
            width: 100
            height: 40
            text: qsTr("Stop")
            anchors.right: start.left
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }

        TableView {
            id: tableView
            selectionMode: 1
            highlightOnFocus: false
            frameVisible: true
            headerVisible: true
            sortIndicatorColumn: 1
            verticalScrollBarPolicy: 1
            sortIndicatorOrder: 1
            sortIndicatorVisible: true
            anchors.bottom: stop.top
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5

            TableViewColumn {
                title: ""
                role: "check"
                width: 20
                delegate: CheckBox {
                    checked: true
                }
            }
            TableViewColumn {
                title: "ID"
                role: "id"
                width: 120
            }
            TableViewColumn {
                title: "Name"
                role: "name"
                width: 168
            }
            TableViewColumn {
                title: "IP Address"
                role: "ip"
            }
            TableViewColumn {
                title: "Status"
                role: "status"
            }
        }
    }
}
