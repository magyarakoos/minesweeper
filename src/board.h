#pragma once

#include <raylib.h>
#include <assert.h>
#include <vector>
#include <array>
#include "point.h"

struct Board {
    Board();

    void SetCell(Point pos, Color c);
    void DrawCell(Point pos) const;
    void Draw() const;

    struct Cell {
        Cell();
        void SetColor(Color color);

        int state;
        bool isBomb;
        Color color;
    };

    Cell& GetCell(Point pos);

    void OpenCell(Point pos);
    void SetBombs(Point start);
    int BombsArount(Point pos);
    
    int unlockCount;
private:

    std::vector<Cell> cells;
    

    std::array<Texture2D, 11> textures;

    Color GetColor(Point pos) const;
};
