import Felgo 3.0
import QtQuick 2.0
import "scenes"

GameWindow {
    id: gameWindow

    screenWidth: 960
    screenHeight: 640

    EntityManager{
        id: entityManager
    }

    MenuScene {
        id: menuScene
    }

    GameScene {
        id: gameScene
    }





}
