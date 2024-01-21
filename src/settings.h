#include <string>
#include <raylib.h>
#include "point.h"

inline constexpr int WIDTH = 800;
inline constexpr int HEIGHT = 800;
inline constexpr int CELL_SIZE = 64;
inline constexpr int CELL_HEIGHT = 10;
inline constexpr int CELL_WIDTH = 12;
inline constexpr int PADDING = 0;
inline constexpr int FPS = 60;
inline constexpr int BOMB_COUNT = CELL_HEIGHT * CELL_WIDTH / 6;
inline constexpr int NUMS_SIZE = 10;

inline constexpr Point SCREEN_POS {
    (WIDTH - (CELL_WIDTH * CELL_SIZE)) / 2,
    HEIGHT - CELL_SIZE * CELL_HEIGHT - (WIDTH - (CELL_WIDTH * CELL_SIZE)) / 2
};

inline constexpr Point DIRS[] = {{-1, -1}, {1, 1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, 1}};

inline const std::string TITLE = "Minesweeper";

inline constexpr KeyboardKey RELOAD = KEY_R;

inline const std::string STATE_0  = "assets/cell/state0.png";
inline const std::string STATE_1  = "assets/cell/state1.png";
inline const std::string STATE_2  = "assets/cell/state2.png";
inline const std::string STATE_3  = "assets/cell/state3.png";
inline const std::string STATE_4  = "assets/cell/state4.png";
inline const std::string STATE_5  = "assets/cell/state5.png";
inline const std::string STATE_6  = "assets/cell/state6.png";
inline const std::string STATE_7  = "assets/cell/state7.png";
inline const std::string STATE_8  = "assets/cell/state8.png";
inline const std::string STATE_9  = "assets/cell/state9.png";
inline const std::string STATE_10 = "assets/cell/state10.png";
inline const std::string STATE_11 = "assets/cell/state11.png";

inline const std::string NUM_0 = "assets/number/0.png";
inline const std::string NUM_1 = "assets/number/1.png";
inline const std::string NUM_2 = "assets/number/2.png";
inline const std::string NUM_3 = "assets/number/3.png";
inline const std::string NUM_4 = "assets/number/4.png";
inline const std::string NUM_5 = "assets/number/5.png";
inline const std::string NUM_6 = "assets/number/6.png";
inline const std::string NUM_7 = "assets/number/7.png";
inline const std::string NUM_8 = "assets/number/8.png";
inline const std::string NUM_9 = "assets/number/9.png";

inline const std::string GUY_0 = "assets/guy/0.png";
inline const std::string GUY_1 = "assets/guy/1.png";
inline const std::string GUY_2 = "assets/guy/2.png";