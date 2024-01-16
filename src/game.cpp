#include <raylib.h>
#include <assert.h>
#include "random.h"
#include "game.h"

Game::Game(Point screenPos, int cellsCount, int cellSize, int padding, int WIDTH, int HEIGHT, int FPS, std::string title)
    :
        board(screenPos, cellsCount, cellsCount, cellSize, padding)
    {

        assert(!GetWindowHandle());

        SetTargetFPS(FPS);
        InitWindow(WIDTH, HEIGHT, title.c_str());

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {

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
    ClearBackground(BLACK);

    board.Draw();
}

void Game::Update() {

}