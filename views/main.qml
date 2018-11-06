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
            onHeightChanged: gameboard.init(gameboard.width, gameboard.height)
        }

        Rectangle{
            color: "#000"
            Layout.preferredWidth: mainwrapper.width
            Layout.preferredHeight: mainwrapper.height * 0.08

            IconButton{
                symbol: "\uf2f9"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                callback: function(){
                    console.log("Restart")
                }
            }

            IconButton{
                id: btnSlower
                symbol: "\uf04a"
                anchors.right: btnStop.left
                anchors.verticalCenter: parent.verticalCenter
            }

            IconButton{
                id: btnStop
                symbol: "\uf04c"
                anchors.centerIn: parent
            }

            IconButton{
                id: btnFaster
                symbol: "\uf04e"
                anchors.left: btnStop.right
                anchors.verticalCenter: parent.verticalCenter
            }

            IconButton{
                symbol: "\uf52b"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                callback: function(){
                    Qt.quit()
                }
            }
        }
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: function(){
            gameboard.nextGeneration();
            gameboard.update();
        }
    }
}
