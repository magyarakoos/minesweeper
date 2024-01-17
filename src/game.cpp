#include <raylib.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include "settings.h"
#include "random_between.h"
#include "game.h"
#include "board.h"

Game::Game() : gameOver(0) {}

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

void Game::GameOver() {
    gameOver = 1;

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            Board::Cell& currCell = board.GetCell({j, i});

            if (currCell.isBomb) {
                currCell.state = 9;
            }
        }
    }
}

void Game::Reload() {
    gameOver = 0;

    board.Construct();
}

void Game::Draw() {
    ClearBackground(RAYWHITE);

    board.Draw();
}

void Game::Update() {
    if (IsKeyPressed(KEY_F5)) {
        
        Reload();
        return;
    }

    if (gameOver) {
        return;
    }

    bool left  = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool right = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

    if (left != right) {

        Point bottomRight;
        bottomRight += WIDTH;
        bottomRight -= SCREEN_POS;

        if (GetMouseX() <  SCREEN_POS.x  || GetMouseY() <  SCREEN_POS.y ||
            GetMouseX() >= bottomRight.x || GetMouseY() >= bottomRight.y
        ) {
            return;
        }

        Point cellPos {
            (GetMouseX() - SCREEN_POS.x) / CELL_SIZE,
            (GetMouseY() - SCREEN_POS.y) / CELL_SIZE 
        };

        if (left) {

            if (board.unlockCount == 0) {

                board.unlockCount = 1;
                board.SetBombs(cellPos);
                board.ZeroSpread(cellPos);

                return;
            }

            board.OpenCell(cellPos);

            const Board::Cell& currCell = board.GetCellConst(cellPos);

            if (currCell.isBomb) {
                GameOver();
            }
        }

        if (right) {
            board.ToggleFlag(cellPos);
        }
    }
}
