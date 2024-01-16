#include <raylib.h>
#include <string>
#include "game.h"

int main() {
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 800;
    constexpr int CELL_SIZE = 40;
    constexpr int CELLS_COUNT = 10;
    constexpr int PADDING = 10;
    constexpr int FPS = 60;

    const Point SCREEN_POS {0, 0};
    const std::string TITLE = "Minesweeper";

    Game game {
        SCREEN_POS,
        CELLS_COUNT,
        CELL_SIZE,
        PADDING,
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