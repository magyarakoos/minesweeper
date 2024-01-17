#pragma once

#include <raylib.h>
#include <assert.h>
#include <vector>
#include <array>
#include "point.h"

struct Board {
    void Construct();
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
    const Cell& GetCellConst(Point pos) const;

    void ZeroSpread(Point pos);
    void OpenCell(Point pos);
    void SetBombs(Point start);
    void ToggleFlag(Point pos);
    
    int unlockCount;
private:
    int BombsAround(Point pos);

    std::vector<Cell> cells;
    

    std::array<Texture2D, 12> textures;

    Color GetColor(Point pos) const;
    int AsIndex(Point pos) const;
};
