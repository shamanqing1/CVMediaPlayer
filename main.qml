import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtMultimedia 5.15
import my.video.filter 1.0
import my.video.cvmedia 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("&File")
//            Action { text: qsTr("&Open"); onTriggered: fileDialog.open()}
//            MenuSeparator {}
//            Action { text: qsTr("&Quit"); onTriggered: Qt.quit() }
//        }
//    }

    header: ToolBar {
        id: toolBar
        visible: false
        RowLayout {
            ToolButton {
                text: qsTr("&Open")
                onClicked: fileDialog.open()
            }

            ToolButton {
                text: qsTr("&Quit")
                onClicked: Qt.quit()
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Please choose a file")
        folder: shortcuts.movies
        nameFilters: [ "Video files (*.mp4 *.avi *.flv *.rm)"]
        onAccepted: {
            console.log(fileDialog.fileUrl)
            player.source = fileUrl
        }
    }

    VideoOutput {
        anchors.fill: parent
        source: player
        filters: [ grayFilter ]
    }

    GrayFilter {
        id: grayFilter
    }

    CVMediaPlayer {
        id: player
    }

    Timer {
        id: toolBarTimer
        interval: 5000
        onTriggered: toolBar.visible = false;
    }

    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: {
            toolBarTimer.start()
            if(!toolBar.visible) {
                toolBar.visible = true
            } else {
                switch(player.PlayingState) {
                    case CVMediaPlayer.PlayingState : player.pause(); break
                    case CVMediaPlayer.PausedState : player.play(); break
                }
            }
        }
    }

}
