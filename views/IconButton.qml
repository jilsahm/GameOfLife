import QtQuick 2.0

Rectangle {
    height: parent.height * 0.8
    width: height
    anchors.leftMargin: parent.height / 10
    anchors.rightMargin: parent.height / 10

    radius: 8
    color: Qt.rgba(0.3, 0.6, 0.3, 0.5)

    MouseArea{
        height: parent.height
        width: parent.width
    }
}
