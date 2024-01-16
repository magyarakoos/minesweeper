#pragma once

#include <raylib.h>
#include <assert.h>
#include <vector>
#include "point.h"

struct Board {
    Board(Point pos, int width, int height, int cellSize, int padding);

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

    const int WIDTH;
    const int HEIGHT;
    const int CELL_SIZE;
    const int PADDING;

    Point screenPos;

    Color GetColor(Point pos) const;
};