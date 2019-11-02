import Felgo 3.0
import QtQuick 2.0

import "../common"

SceneBase {
  id:menuScene

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
    text: "MultiSceneMultiLevel"
  }
}
