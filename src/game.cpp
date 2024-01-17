#include <raylib.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <string>
#include "graphics.h"
#include "settings.h"
#include "random_between.h"
#include "game.h"
#include "board.h"

Game::Game() : gameOver(0), frameCounter(0) {}

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

    if (!gameOver) frameCounter++;
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
    frameCounter = 0;

    board.Construct();
}

void Game::Draw() {
    ClearBackground(Color{156, 156, 156, 255});

    int text_size = 100;
    
    DrawRect({SCREEN_POS.x, SCREEN_POS.x}, {WIDTH - 2 * SCREEN_POS.x, text_size / 10 * 9}, BLACK);

    unsigned sec = frameCounter / FPS;

    if (sec >= 1000) {
        GameOver();
    }
    
    std::string secStr;

    for (int i = 2; i >= 0; i--) {
        secStr += (char)(sec % 10) + '0';
        sec /= 10;
    }

    std::reverse(secStr.begin(), secStr.end());

    DrawTextEx(
        Font{FONT_DEFAULT}, 
        secStr.c_str(), 
        {
            (float)(SCREEN_POS.x + text_size / 10), 
            (float)(SCREEN_POS.x)
        }, 
        text_size, 
        text_size / 10,
        RED
    );

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
        bottomRight -= SCREEN_POS.x;

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

            if (!board.gameStarted) {

                board.gameStarted = 1;
                board.SetBombs(cellPos);
                board.ZeroSpread(cellPos);

                return;
            }

            int exitCode = board.OpenCell(cellPos);

            const Board::Cell& currCell = board.GetCellConst(cellPos);

            if (currCell.isBomb || exitCode) {
                GameOver();
            }
        }

        board.ToggleFlag(cellPos);
    }
}
