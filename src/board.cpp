#include "board.h"

Board::Cell::Cell()
    :
    exists(0),
    color(WHITE) {}

void Board::Cell::SetColor(Color c) {
    color = c;
    exists = 1;
}

void Board::Cell::Remove() noexcept {
    exists = 0;
}

Board::Board(int x, int y, int width, int height, int cellSize)
    :
        screenX(x),
        screenY(y),
        WIDTH(width),
        HEIGHT(height),
        CELL_SIZE(cellSize)
    {
        assert(width > 0 && height > 0);
        assert(cellSize > 0);

        cells.resize(WIDTH * HEIGHT);
    }

void Board::SetCell(int x, int y, Color c) {
    
    assert(x >= 0 && y >= 0);
    assert(x < WIDTH && y < HEIGHT);

    int index = WIDTH * y + x;

    cells[index].SetColor(c);
}

Color Board::GetColor(int x, int y) const {
    
    assert(x >= 0 && y >= 0);
    assert(x < WIDTH && y < HEIGHT);

    int index = WIDTH * y + x;

    return cells[index].color;
}

void Board::DrawCell(int x, int y) const {

    DrawRectangle(
        screenX + x * CELL_SIZE, 
        screenY + y * CELL_SIZE, 
        CELL_SIZE, 
        CELL_SIZE, 
        GetColor(x, y)
    );
}

void Board::Draw() const {
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            DrawCell(i, j);
        }
    }
}