#pragma once

#include <string>

struct Game {
    Game(int WIDTH, int HEIGHT, int FPS, char* title);
    
    Game(const Game& g) = delete;

    Game& operator=(const Game& g) = delete;

    ~Game() noexcept;

    bool TriggerClose() const;
    void Tick();

private:
    void Draw();
    void Update();
};