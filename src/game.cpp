#include "game.h"

#include <raylib.h>
#include <assert.h>

Game::Game(int WIDTH, int HEIGHT, int FPS, char* title) {

    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, title);
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
}

void Game::Update() {

}