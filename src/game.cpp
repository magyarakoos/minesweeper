#include <raylib.h>
#include <assert.h>
#include "settings.h"
#include "random.h"
#include "game.h"

Game::Game() {
        assert(!GetWindowHandle());

        SetTargetFPS(FPS);
        InitWindow(WIDTH, HEIGHT, TITLE.c_str());

        for (int i = 0; i < CELL_HEIGHT; i++) {
            for (int j = 0; j < CELL_WIDTH; j++) {

                unsigned char randomGray = random(0, 255);

                Color randomColor {
                    randomGray,
                    randomGray,
                    randomGray,
                    255
                };

                board.SetCell({j, i}, randomColor);
            }
        }
    }

Game::~Game() {
    assert(GetWindowHandle());

    CloseWindow();
}

bool Game::TriggerClose() const {
    return WindowShouldClose();
}

void Game::Tick() {

    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void Game::Draw() {
    ClearBackground(RAYWHITE);

    board.Draw();
}

void Game::Update() {

}
