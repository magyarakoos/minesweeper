#pragma once

#include <string>
#include "board.h"

struct Game {
    Game(Point screenPos, int cellsCount, int cellSize, int padding, int WIDTH, int HEIGHT, int FPS, std::string title);
    
    Game(const Game& g) = delete;

    Game& operator=(const Game& g) = delete;

    ~Game() noexcept;

    bool TriggerClose() const;
    void Tick();

private:
    void Draw();
    void Update();

    Board board;
};