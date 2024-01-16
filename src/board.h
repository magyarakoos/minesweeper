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
        void Remove() noexcept;

        int state;
        bool exists;
        Color color;
    };

    Cell& GetCell(Point pos);

    void OpenCell(Point pos);
private:

    std::vector<Cell> cells;
    
    int unlockCount;

    std::array<Texture2D, 11> textures;

    Color GetColor(Point pos) const;
};
