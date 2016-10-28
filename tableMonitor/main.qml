import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Table")
    id: root

    signal editSign(string id, string name, string ipaddr)
    signal appendSign(string name, string ipaddr)

    property alias mouseArea: mouseArea

    MainForm {
//        mouseArea.onClicked: {
//            dropMenu.popup()
//        }
//        tableView.model: tableModel
        anchors.fill: parent
    }

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
        onClicked: dropMenu.popup()

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
            model: tableModel

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

    function appendRow(val) {
        tableModel.append({idcol: val[1], name: val[2], ip: val[3], status: val[4]})
        return
    }

    function modifyRow(val) {
        tableModel.set(val[1], {name: val[2], ip: val[3], status: val[4]})
        return
    }

    property bool creating: true

    function addRow() {
        creating = true
        editWindow.visible = true
    }

    function editRow() {
        creating = false
        editWindow.visible = true
    }

    ListModel {
        id: tableModel
    }

    Menu {
        id: dropMenu
        MenuItem{
               text: "Edit"
               onTriggered: editRow()
        }
        MenuItem{
               text: "Delete"
        }
        MenuItem{
               text: "Add"
               onTriggered: addRow()
        }
    }

    Window {
        id: editWindow
        visible: false
        title: "Edit Window"
        width: 300
        height: 150

        Rectangle {
            id: rectangle1
            color: "#ffffff"
            anchors.bottom: save.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            anchors.topMargin: 10

            Text {
                id: nameT
                width: 79
                height: 30
                text: qsTr("Name:")
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 24
            }

            TextField {
                id: nametf
                height: 30
                anchors.right: parent.right
                anchors.rightMargin: 5
                font.pointSize: 18
                anchors.left: nameT.right
                anchors.leftMargin: 10

            }

            Text {
                id: ipaddr
                x: 0
                y: 0
                width: 79
                height: 30
                text: qsTr("IP:")
                anchors.top: nameT.bottom
                anchors.left: parent.left
                anchors.topMargin: 15
                anchors.leftMargin: 0
                font.pixelSize: 24
            }

            TextField {
                id: ipaddrtf
                height: 30
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.top: nameT.bottom
                anchors.topMargin: 15
                anchors.left: ipaddr.right
                anchors.leftMargin: 10
                font.pointSize: 18
            }
        }

        Button {
            id: save
            x: 139
            y: 364
            width: 123
            height: 26
            text: qsTr("Save")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            onClicked: {
                if (creating) {
                    appendSign(nametf.text, ipaddrtf.text)
                    nametf.text = ""
                    ipaddrtf.text = ""
                    editWindow.visible = false
                } else {
                    var tmp = tableModel.get(tableView.currentRow).idcol
                    editSign(tmp, nametf.text, ipaddrtf.text)
                    nametf.text = ""
                    ipaddrtf.text = ""
                    editWindow.visible = false
                }
            }
        }
    }
}
