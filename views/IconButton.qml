import QtQuick 2.0

Rectangle {
    property var    callback : function(){}
    property string symbol   : "?"

    id: button
    height: parent.height * 0.8
    width: height
    anchors.leftMargin: parent.height / 10
    anchors.rightMargin: parent.height / 10
    radius: 10
    color: Qt.rgba(0.3, 0.6, 0.3, 0.3)

    Text{
        font.family: Fonts.icons
        font.pointSize: 24
        text: parent.symbol
        color: Qt.rgba(0.5, 1.0, 0.5, 1.0)
        anchors.centerIn: parent
    }

    MouseArea{
        height: parent.height
        width: parent.width
        onClicked: function(){
            animation.running = true
            button.callback()
        }
    }

    SequentialAnimation {
        id: animation
        PropertyAnimation {
            target: button
            property: "color"
            to: Qt.rgba(0.4, 0.8, 0.4, 0.8)
            duration: 150
        }
        PropertyAnimation {
            target: button
            property: "color"
            to: Qt.rgba(0.3, 0.6, 0.3, 0.3)
            duration: 150
        }
    }
}
