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

        guys = {
            LoadTexture(GUY_0.c_str()),
            LoadTexture(GUY_1.c_str()),
            LoadTexture(GUY_2.c_str())
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

void Game::GameOver(bool won) {
    gameOver = 1 + won;

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            Board::Cell& currCell = board.GetCell({j, i});

            if (currCell.isBomb) {
                currCell.state = (won ? 11 : 9);
            }
        }
    }
}

void Game::Reload() {
    gameOver = 0;
    frameCounter = 0;
    bombUserCount = BOMB_COUNT;
    
    board.Construct();
}

void Game::Draw() {
    ClearBackground(Color{198, 198, 198, 255});

    std::array<int, 3> bombs;

    unsigned userCountCopy = bombUserCount;

    for (int i = 2; i >= 0; i--) {
        bombs[i] = userCountCopy % 10;
        userCountCopy /= 10;
    }

    DrawClock(
        {
            numbers[bombs[0]], 
            numbers[bombs[1]], 
            numbers[bombs[2]]
        }, 
        {
            SCREEN_POS.x, 
            SCREEN_POS.x
        }, 
        NUMS_SIZE
    );

    std::array<int, 3> seconds;

    unsigned sec = frameCounter / FPS;

    if (sec >= 1000) {
        GameOver(0);
    }

    for (int i = 2; i >= 0; i--) {
        seconds[i] = sec % 10;
        sec /= 10;
    }

    DrawClock(
        {
            numbers[seconds[0]], 
            numbers[seconds[1]], 
            numbers[seconds[2]]
        }, 
        {
            WIDTH - SCREEN_POS.x - NUMS_SIZE * 19, 
            SCREEN_POS.x
        }, 
        NUMS_SIZE
    );

    float guySize = (float)NUMS_SIZE * 9 / 21;

    DrawSprite(guys[gameOver], {WIDTH / 2 - NUMS_SIZE * 9 / 2, SCREEN_POS.x}, guySize);

    board.Draw();
}

void Game::Update() {
    if (IsKeyPressed(RELOAD)) {
        
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

        if (GetMouseX() <  SCREEN_POS.x  || GetMouseY() <  SCREEN_POS.y
        ) {
            return;
        }

        Point cellPos {
            (GetMouseX() - SCREEN_POS.x) / CELL_SIZE,
            (GetMouseY() - SCREEN_POS.y) / CELL_SIZE 
        };

        if (cellPos.x >= CELL_WIDTH || cellPos.y >= CELL_HEIGHT) {
            return;
        }

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
                GameOver(0);
            }
        }

        bombUserCount += board.ToggleFlag(cellPos);

        if (bombUserCount == (unsigned)-1) {
            bombUserCount = 0;
        }

        if (std::all_of(board.cells.begin(), board.cells.end(), 
            [](Board::Cell cell){ return cell.state != 0 && (cell.isBomb ? cell.state == 11 : cell.state != 11); })
            ) {
            
            GameOver(1);
        }
    }
}
