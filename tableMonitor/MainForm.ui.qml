import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2


Item {
    id: item1
    width: 640
    height: 480

    property alias tableView: tableView
    property alias mouseArea: mouseArea


    Button {
        id: stop
        x: 356
        y: 428
        width: 134
        height: 44
        text: qsTr("Stop")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: start.left
        anchors.rightMargin: 10
    }

    Button {
        id: start
        x: 500
        y: 428
        width: 134
        height: 44
        text: qsTr("Start")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
    }

    RowLayout {
        width: 640
        height: 480
        anchors.centerIn: parent
    }
    MouseArea {
        id: mouseArea
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: stop.top
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        acceptedButtons: Qt.RightButton

        TableView {
            id: tableView
            anchors.fill: parent
            opacity: 1
            clip: false
            selectionMode: 1
            horizontalScrollBarPolicy: 1
            highlightOnFocus: true
            frameVisible: true
            headerVisible: true
            sortIndicatorColumn: 1
            verticalScrollBarPolicy: 0
            sortIndicatorOrder: 1
            sortIndicatorVisible: true

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
                role: "idcol"
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
