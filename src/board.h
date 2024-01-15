#pragma once

#include <raylib.h>
#include <assert.h>
#include <vector>

struct Board {
    Board(int x, int y, int width, int height, int cellSize);

    void SetCell(int x, int y, Color c);
    void DrawCell(int x, int y) const;
    void Draw() const;

private:
    struct Cell {
        Cell();
        void SetColor(Color color);
        void Remove();

        bool exists;
        Color color;
    };

    std::vector<Cell> cells;

    const int WIDTH;
    const int HEIGHT;
    const int CELL_SIZE;

    int screenX;
    int screenY;

    Color GetColor(int x, int y) const;
};