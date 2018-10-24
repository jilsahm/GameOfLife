import QtQuick 2.11
import QtQuick.Layouts 1.3

import game 1.0

Rectangle {
    id: mainwrapper
    visible: true

    ColumnLayout{
        spacing: 0

        GameBoard{
            visible: true
            id: gameboard
            Layout.preferredWidth: mainwrapper.width
            Layout.preferredHeight: mainwrapper.height * 0.92
        }

        Rectangle{
            color: "#000"
            Layout.preferredWidth: mainwrapper.width
            Layout.preferredHeight: mainwrapper.height * 0.08

            IconButton{
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

            IconButton{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: gameboard.update()
    }
}
