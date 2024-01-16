#include "board.h"
#include "settings.h"
#include "graphics.h"

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

    state0 = LoadTexture(STATE_0.c_str());
}

void Board::SetCell(Point pos, Color c) {

    assert(pos.x >= 0 && pos.y >= 0);
    assert(pos.x < CELL_WIDTH && pos.y < CELL_HEIGHT);

    int index = CELL_WIDTH * pos.y + pos.x;

    cells[index].SetColor(c);
}

Color Board::GetColor(Point pos) const {

    assert(pos.x >= 0 && pos.y >= 0);
    assert(pos.x < CELL_WIDTH && pos.y < CELL_HEIGHT);

    int index = CELL_WIDTH * pos.y + pos.x;

    return cells[index].color;
}

void Board::DrawCell(Point pos, Texture2D texture) const {

    Point cellPos = pos;

    cellPos *= CELL_SIZE;
    cellPos += SCREEN_POS;

    DrawSprite(texture, cellPos, 1);
}

void Board::Draw() const {

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            DrawCell({j, i});
        }
    }
}
