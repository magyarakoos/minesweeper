#include <raylib.h>
#include <string>
#include "game.h"
#include "settings.h"

int main() {

    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    
    Game game;

    while (!game.TriggerClose()) {
        game.Tick();
    }

    return 0;
}
