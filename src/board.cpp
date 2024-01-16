#include <iostream>
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

Board::Board(Point pos, int width, int height, int cellSize, int padding)
    :
        screenPos(pos),
        WIDTH(width),
        HEIGHT(height),
        CELL_SIZE(cellSize),
        PADDING(padding)
    {
        assert(width > 0 && height > 0);
        assert(cellSize > 0);

        cells.resize(WIDTH * HEIGHT);
    }

void Board::SetCell(Point pos, Color c) {

    assert(pos.GetX() >= 0 && pos.GetY() >= 0);
    assert(pos.GetX() < WIDTH && pos.GetY() < HEIGHT);

    int index = WIDTH * pos.GetY() + pos.GetX();

    cells[index].SetColor(c);
}

Color Board::GetColor(Point pos) const {

    assert(pos.GetX() >= 0 && pos.GetY() >= 0);
    assert(pos.GetX() < WIDTH && pos.GetY() < HEIGHT);

    int index = WIDTH * pos.GetY() + pos.GetX();

    return cells[index].color;
}

void Board::DrawCell(Point pos) const {

    DrawRectangle(
        pos.GetX() * CELL_SIZE + PADDING,
        pos.GetY() * CELL_SIZE + PADDING,
        CELL_SIZE - PADDING,
        CELL_SIZE - PADDING,
        GetColor(pos)
    );
}

void Board::Draw() const {

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            DrawCell({j, i});
        }
    }
}