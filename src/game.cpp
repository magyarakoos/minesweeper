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

Game::Game() 
    : 
        gameOver(0), 
        frameCounter(0),
        bombUserCount(BOMB_COUNT)
    {
        numbers = {
            LoadTexture(NUM_0.c_str()),
            LoadTexture(NUM_1.c_str()),
            LoadTexture(NUM_2.c_str()),
            LoadTexture(NUM_3.c_str()),
            LoadTexture(NUM_4.c_str()),
            LoadTexture(NUM_5.c_str()),
            LoadTexture(NUM_6.c_str()),
            LoadTexture(NUM_7.c_str()),
            LoadTexture(NUM_8.c_str()),
            LoadTexture(NUM_9.c_str()),
        };
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
    ClearBackground(RAYWHITE);

    std::array<int, 3> bombs;



    DrawClock({numbers[0], numbers[7], numbers[9]}, {SCREEN_POS.x, SCREEN_POS.x}, NUMS_SIZE);

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

        bombUserCount += board.ToggleFlag(cellPos);

        if (bombUserCount == (unsigned)-1) {
            bombUserCount = 0;
        }

        if (std::all_of(board.cells.begin(), board.cells.end(), 
            [](Board::Cell cell){ return cell.state != 0; })
            ) {
            
            GameOver();
        }
    }
}
