import Felgo 3.0
import QtQuick 2.0
import "../common"

SceneBase {
  id:gameScene

  // background
  Rectangle {
    anchors.fill: parent.gameWindowAnchorItem
    color: "#dd94da"
  }

  Column {
      MenuButton {
        text: "Back"
        anchors.right: gameScene.gameWindowAnchorItem.right
        anchors.rightMargin: 10
        anchors.top: gameScene.gameWindowAnchorItem.top
        anchors.topMargin: 10
        onClicked: backButtonPressed()
      }

  }


  onBackButtonPressed: gameWindow.state = "menu"
}
