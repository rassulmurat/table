import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2


ApplicationWindow {
    visible: true
    width: 740
    height: 480
    title: qsTr("Iperf Tester")
    id: root

    signal saveSign()
    signal saveAsSign(url path)
    signal loadSign()
    signal loadAsSign(url path)
    signal exportToOdt(url path)
    menuBar: MenuBar{
        Menu{
            title: "File";
            MenuItem{
                text: "Save"
                onTriggered: saveSign()
            }
            MenuItem{
                text: "Save As"
                onTriggered: saveFileDialog.visible = true
            }
            MenuItem{
                text: "Load"
                onTriggered: loadSign()
            }
            MenuItem{
                text: "Load From"
                onTriggered: loadFileDialog.visible = true
            }
        }
        Menu{
            title: "Export"
            MenuItem{
                text: "Text File"
                onTriggered: exportDialog.visible = true
            }
        }
    }

    FileDialog{
        id: exportDialog
        visible: false
        title: "Save Table As"
        nameFilters: "Text File(*.odt)"
        selectExisting: false
        folder: shortcuts.home
        onAccepted: {
            exportToOdt(exportDialog.fileUrl)
        }
    }

    FileDialog{
        id: saveFileDialog
        visible: false
        title: "Save Table As"
        nameFilters: "*.csv"
        selectExisting: false
        folder: shortcuts.home
        onAccepted: {
            saveAsSign(saveFileDialog.fileUrl)
        }
    }
    FileDialog{
        id: loadFileDialog
        visible: false
        title: "Save Table As"
        nameFilters: "*.csv"
        selectExisting: true
        folder: shortcuts.home
        onAccepted: {
            loadAsSign(loadFileDialog.fileUrl)
        }
    }

    signal editSign(string id, string name, string ipaddr)
    signal appendSign(string name, string ipaddr)
    signal removeSign(string id)
    signal startSign()
    signal stopSign()
    signal pouseSign()
    signal checkSign(string id, string bool)

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
        onClicked: stopClicked()
        enabled: false

        Image {
            id: stopImg
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            anchors.rightMargin: 5
            anchors.leftMargin: 100
            anchors.fill: parent
            source: "stop_but.png"
        }
    }

    function stopClicked() {
        stop.enabled = false
        start.enabled = true
        progressBarText.text = "Stoped"
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

        Image {
            id: startImg
            anchors.rightMargin: 5
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            z: 1
            anchors.leftMargin: 100
            anchors.fill: parent
            source: "play-button-th.png"
        }
    }

    function startClicked() {
        stop.enabled = true
        start.enabled = false
        progressBarText.text = "Testing"
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
                width: tableView.width/5
            }
            TableViewColumn {
                title: "Name"
                role: "name"
                width: tableView.width/5
            }
            TableViewColumn {
                title: "IP Address"
                role: "ip"
                width: tableView.width/5
            }
            TableViewColumn {
                title: "Status"
                role: "status"
                width: tableView.width/5
            }
            TableViewColumn {
                title: "Latency"
                role: "lat"
                width: tableView.width/5
            }
        }
    }

    function checkBoxClicked(val) {
        tableModel.get(val).check = {checked: !tableModel.get(val).check.checked}
        checkSign(val, tableModel.get(val).check.checked)
    }

    function checkedAdd(val) {
        progressBar.value = val
        if (1 == progressBar.value) {
            stop.enabled = false
            start.enabled = true
        }
    }

    function appendRow(val) {
        var tmp
        if (val[0] == "true") {
            tmp = true
        } else {
            tmp = false
        }
        tableModel.append({check: {checked: tmp}, idcol: val[1], name: val[2], ip: val[3], status: val[4], lat: val[5]})
    }

    function modifyRow(val) {
        tableModel.set(val[1], {check: {checked: val[0]}, name: val[2], ip: val[3], status: val[4], lat: val[5]})
        return
    }

    function setResponse(val) {
        tableModel.set(val[0], {status: val[1], lat: val[2]})
    }

    function setRole(val) {
        tableModel.set(id, {rol: value})
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

            Text {
                id: progressBarText
                width: 20
                color: "#2a2674"
                text: qsTr("Not Running")
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.rightMargin: 0
                font.italic: true
                opacity: 0.6
                textFormat: Text.AutoText
                wrapMode: Text.NoWrap
                font.family: "Courier"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24

                Text {
                    id: progressTotal
                    x: 396
                    width: 50
                    color: "#2a2674"
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    opacity: 0.6
                    font.italic: true
                    font.family: "Courier"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 24
                }
            }
        }
    }

    function finished() {
        progressBarText.text = "Finished";
    }

    function totalChange(val) {
        progressTotal.text = val
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
        nametf.text = ""
        ipaddrtf.text = ""
        editWindow.visible = true
    }
    //Function for tight click menu
    function editRow() {
        creating = false
        nametf.text = tableModel.get(tableView.currentRow).name
        ipaddrtf.text = tableModel.get(tableView.currentRow).ip
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
                    editWindow.visible = false
                } else {
                    var tmp = tableModel.get(tableView.currentRow).idcol
                    editSign(tmp, nametf.text, ipaddrtf.text)
                    editWindow.visible = false
                }
            }
        }
    }


}
