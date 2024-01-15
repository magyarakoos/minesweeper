#include <raylib.h>
#include <string>
#include "game.h"

int main() {
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 450;
    constexpr int FPS = 60;
    constexpr char * TITLE = "Minesweeper";

    Game game {
        WIDTH,
        HEIGHT,
        FPS,
        TITLE
    };

    while (!game.TriggerClose()) {

        game.Tick();
    }

    return 0;
}