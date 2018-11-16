import QtQuick 2.11
import QtQuick.Layouts 1.3

import game 1.0

Rectangle {
    id: mainwrapper
    color: "#000"
    visible: true

    ColumnLayout{
        spacing: 0

        GameBoard{
            visible: true
            id: gameboard
            Layout.preferredWidth: mainwrapper.width
            Layout.preferredHeight: mainwrapper.height * 0.92
            Layout.fillHeight: true
            Layout.margins: 0
            onHeightChanged: gameboard.init(gameboard.width, gameboard.height)
            MouseArea{
                width: parent.width
                height: parent.height
                onClicked: function(){
                    //console.log(mouseX, mouseY);
                    gameboard.spawnCell(mouseX, mouseY);
                }
            }
        }

        Rectangle{
            color: "#000"
            Layout.preferredWidth: mainwrapper.width
            Layout.preferredHeight: mainwrapper.height * 0.08
            Layout.fillHeight: true
            Layout.margins: 0

            IconButton{
                symbol: "\uf2f9"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                callback: function(){
                    //console.log("Restart")
                    gameboard.init(gameboard.width, gameboard.height);
                }
            }

            IconButton{
                id: btnSlower
                symbol: "\uf04a"
                anchors.right: btnStop.left
                anchors.verticalCenter: parent.verticalCenter
                callback: function(){
                    // Decrease speed
                    if (!timer.running){
                        timer.start();
                    }
                    timer.interval = 1000;
                }
            }

            IconButton{
                id: btnStop
                symbol: "\uf04c"
                anchors.centerIn: parent
                callback: function(){
                    // Pause
                    timer.stop();
                }
            }

            IconButton{
                id: btnFaster
                symbol: "\uf04e"
                anchors.left: btnStop.right
                anchors.verticalCenter: parent.verticalCenter
                callback: function(){
                    // Increase speed
                    if (!timer.running){
                        timer.start();
                    }
                    timer.interval = 200;
                }
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
        id: timer
        interval: 200
        running: true
        repeat: true
        onTriggered: function(){
            gameboard.nextGeneration();
            gameboard.update();
        }
    }
}
