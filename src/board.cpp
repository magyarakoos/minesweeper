#include <iostream>
#include "board.h"
#include "settings.h"

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

Board::Board() {
    assert(CELL_WIDTH > 0 && CELL_HEIGHT > 0);
    assert(CELL_SIZE > 0);

    cells.resize(CELL_WIDTH * CELL_HEIGHT);
}

void Board::SetCell(Point pos, Color c) {

    assert(pos.GetX() >= 0 && pos.GetY() >= 0);
    assert(pos.GetX() < CELL_WIDTH && pos.GetY() < CELL_HEIGHT);

    int index = CELL_WIDTH * pos.GetY() + pos.GetX();

    cells[index].SetColor(c);
}

Color Board::GetColor(Point pos) const {

    assert(pos.GetX() >= 0 && pos.GetY() >= 0);
    assert(pos.GetX() < CELL_WIDTH && pos.GetY() < CELL_HEIGHT);

    int index = CELL_WIDTH * pos.GetY() + pos.GetX();

    return cells[index].color;
}

void Board::DrawCell(Point pos) const {

    Point cellPos = pos;

    cellPos *= CELL_SIZE;
    cellPos += SCREEN_POS;

    DrawRectangle(
        cellPos.GetX(),
        cellPos.GetY(),
        CELL_SIZE - PADDING,
        CELL_SIZE - PADDING,
        GetColor(pos)
    );
}

void Board::Draw() const {

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            DrawCell({j, i});
        }
    }
}
