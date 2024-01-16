#include <raylib.h>
#include <assert.h>
#include <iostream>
#include "settings.h"
#include "random.h"
#include "game.h"
#include "board.h"

Game::Game() {
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        Point cellPos {
            (GetMouseX() - SCREEN_POS.x) / CELL_SIZE,
            (GetMouseY() - SCREEN_POS.y) / CELL_SIZE 
        };

        Board::Cell& currCell = board.GetCell(cellPos);

        std::cout << cellPos.x << ' ' << cellPos.y << '\n';
        
        if (currCell.state != 0) return;

        
    }
}
