#pragma once

#include <string>
#include <array>
#include "board.h"

struct Game {
    Game();
    Game(const Game& g) = delete;

    Game& operator=(const Game& g) = delete;

    ~Game() noexcept;

    bool TriggerClose() const;
    void Tick();
    void GameOver(bool won);

    // 0: game currently going
    // 1: game over (lost)
    // 2: game over (won)
    int gameOver;
    unsigned frameCounter;
    unsigned bombUserCount;
private:
    void Draw();
    void Update();
    void Reload();

    Board board;

    std::array<Texture2D, 10> numbers;
    std::array<Texture2D, 3> guys;
};
