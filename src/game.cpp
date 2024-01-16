#include <raylib.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include "settings.h"
#include "random_between.h"
#include "game.h"
#include "board.h"

Game::Game() {
    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            unsigned char randomGray = random_between(0, 255);

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

        if (board.unlockCount == 0) {

            board.SetBombs(cellPos);
        }

        Board::Cell& currCell = board.GetCell(cellPos);

        if (currCell.isBomb) {
            currCell.state = 9;
            return;
        }

        board.OpenCell(cellPos);
    }
}
