#include <string>
#include "point.h"

inline constexpr int WIDTH = 800;
inline constexpr int HEIGHT = 768;
inline constexpr int CELL_SIZE = 128;
inline constexpr int CELL_HEIGHT = 5;
inline constexpr int CELL_WIDTH = 6;
inline constexpr int PADDING = 0;
inline constexpr int FPS = 60;
inline constexpr int BOMB_COUNT = CELL_HEIGHT * CELL_WIDTH / 6;

inline constexpr Point SCREEN_POS {
    (WIDTH - (CELL_WIDTH * CELL_SIZE)) / 2,
    HEIGHT - CELL_SIZE * CELL_HEIGHT - (WIDTH - (CELL_WIDTH * CELL_SIZE)) / 2
};

constexpr Point DIRS[] = {{-1, -1}, {1, 1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, 1}};

const std::string TITLE = "Minesweeper";

const std::string STATE_0 = "assets/state0.png";
const std::string STATE_1 = "assets/state1.png";
const std::string STATE_2 = "assets/state2.png";
const std::string STATE_3 = "assets/state3.png";
const std::string STATE_4 = "assets/state4.png";
const std::string STATE_5 = "assets/state5.png";
const std::string STATE_6 = "assets/state6.png";
const std::string STATE_7 = "assets/state7.png";
const std::string STATE_8 = "assets/state8.png";
const std::string STATE_9 = "assets/state9.png";
const std::string STATE_10 = "assets/state10.png";
const std::string STATE_11 = "assets/state11.png";
