import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtMultimedia 5.15
import my.video.filter 1.0
import my.video.cvmedia 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&Open"); onTriggered: fileDialog.open()}
            MenuSeparator {}
            Action { text: qsTr("&Quit"); onTriggered: Qt.quit() }
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
//        filters: [ grayFilter ]
    }

    GrayFilter {
        id: grayFilter
    }


//    MediaPlayer {
//        id: player
//        autoPlay: true
//    }
    CVMediaPlayer {
        id: player
    }

    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: {
            switch(player.playbackState) {
                case MediaPlayer.PlayingState : player.pause(); break
                case MediaPlayer.PausedState : player.play(); break
            }
        }
    }

}
