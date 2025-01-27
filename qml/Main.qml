import Felgo 3.0
import QtQuick 2.0
import "scenes"

GameWindow {
    state: "menu"

    id: gameWindow

    screenWidth: 960
    screenHeight: 640

    states: [
        State {
            name: "menu"
            PropertyChanges {
                target: menuScene
                opacity: 1.0
            }
            PropertyChanges {
                target: gameWindow
                activeScene: menuScene

            }
        }

        ,State {
            name: "game"
            PropertyChanges {
                target: gameScene
                opacity: 1;
            }
            PropertyChanges {
                target: gameWindow
                activeScene: gameScene

            }
        }

    ]


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
