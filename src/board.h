#pragma once

#include <raylib.h>
#include <assert.h>
#include <vector>
#include "point.h"

struct Board {
    Board();

    void SetCell(Point pos, Color c);
    void DrawCell(Point pos) const;
    void Draw() const;

private:
    struct Cell {
        Cell();
        void SetColor(Color color);
        void Remove() noexcept;

        bool exists;
        Color color;
    };

    std::vector<Cell> cells;

    Color GetColor(Point pos) const;
};
