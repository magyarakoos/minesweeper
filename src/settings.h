#include <string>
#include "point.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr int CELL_SIZE = 45;
constexpr int CELL_HEIGHT = 10;
constexpr int CELL_WIDTH = 10;
constexpr int PADDING = 10;
constexpr int FPS = 60;

const Point SCREEN_POS {
    (WIDTH - (CELL_WIDTH * CELL_SIZE)) / 2,
    (HEIGHT - (CELL_HEIGHT * CELL_SIZE)) / 2
};

const std::string TITLE = "Minesweeper";
