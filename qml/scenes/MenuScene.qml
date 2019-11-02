import Felgo 3.0
import QtQuick 2.0

Scene {
    id: menuScene

    // signal indicating that the selectLevelScene should be displayed
    signal selectLevelPressed
    // signal indicating that the creditsScene should be displayed
    signal creditsPressed
    // signal indicating that the settingsScene should be displayed
    signal settingsPressed

    // background
    Rectangle {
        anchors.fill: parent.gameWindowAnchorItem
        color: "#47688e"
    }

    // the "logo"
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 30
        font.pixelSize: 30
        color: "#e9e9e9"
        text: "Menu Scene"
    }

    // menu
    Column {
        anchors.centerIn: parent
        spacing: 10

        // TODO replace the buttons with your custom styled buttons
        GameButton {
            text: "Levels"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                // TODO load your levelselection scene here or start the game
                selectLevelPressed()
            }
        }

        GameButton {
            text: "Settings"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                // TODO load your settings scene here
                settingsPressed()
            }
        }

        GameButton {
            text: "Credits"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                // TODO load your credits scene here
                creditsPressed()
            }
        }
    }
}
