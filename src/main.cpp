#include <raylib.h>
#include <string>
#include "game.h"

int main() {
    
    Game game;

    while (!game.TriggerClose()) {
        game.Tick();
    }

    return 0;
}
