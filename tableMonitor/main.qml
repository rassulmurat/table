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
    signal removeSign(string id)
    signal startSign()
    signal stopSign()
    signal pouseSign()
    signal checkSign(string id, string bool)

    property alias mouseArea: mouseArea

    MainForm {
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
        onClicked: stopClicked()
        enabled: false
    }

    function stopClicked() {
        stop.enabled = false
        start.enabled = true
        stopSign()
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
        onClicked: startClicked()
    }

    function startClicked() {
        stop.enabled = true
        start.enabled = false
        startSign()
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
                    checked: tableModel.get(styleData.row).check.checked
                    onClicked: checkBoxClicked(styleData.row)
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

    function checkBoxClicked(val) {
        tableModel.get(val).check = {checked: !tableModel.get(val).check.checked}
        checkSign(val, tableModel.get(val).check.checked)
    }

    function checkedAdd(val) {
       progressBar.value = val
    }

    function appendRow(val) {
        var tmp
        if (val[0] == "true") {
            tmp = true
        } else {
            tmp = false
        }
        tableModel.append({check: {checked: tmp}, idcol: val[1], name: val[2], ip: val[3], status: val[4]})
    }

    function modifyRow(val) {
        tableModel.set(val[1], {check: {checked: val[0]}, name: val[2], ip: val[3], status: val[4]})
        return
    }

    function removeRow() {
        tableModel.remove(tableView.currentRow)
        removeSign(tableView.currentRow)
    }

    property bool creating: true

    ListModel {
        id: tableModel
    }

    Rectangle {
        id: counterRect
        color: "#00000000"
        border.color: "#00000000"
        anchors.top: mouseArea.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: stop.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        ProgressBar {
            id: progressBar
            anchors.fill: parent
        }
    }

    /*
      * Drop menu(Right click)
      */
    Menu {
        id: dropMenu
        MenuItem{
               text: "Add"
               onTriggered: addRow()
        }
        MenuItem{
               text: "Edit"
               onTriggered: editRow()
        }
        MenuItem{
               text: "Delete"
               onTriggered: removeRow()
        }
    }
//Function for right click menu
    function addRow() {
        creating = true
        editWindow.visible = true
    }
//Function for tight click menu
    function editRow() {
        creating = false
        editWindow.visible = true
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
