import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: item1
    width: 400
    height: 400

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
            font.pointSize: 24
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
            font.pointSize: 24
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
    }
}
