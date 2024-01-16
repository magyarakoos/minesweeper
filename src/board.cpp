#include "board.h"
#include "settings.h"
#include "graphics.h"

Board::Cell::Cell()
    :
    state(0),
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

    unlockCount = 0;

    textures = {
        LoadTexture(STATE_0.c_str()),
        LoadTexture(STATE_1.c_str()),
        LoadTexture(STATE_2.c_str()),
        LoadTexture(STATE_3.c_str()),
        LoadTexture(STATE_4.c_str()),
        LoadTexture(STATE_5.c_str()),
        LoadTexture(STATE_6.c_str()),
        LoadTexture(STATE_7.c_str()),
        LoadTexture(STATE_8.c_str()),
        LoadTexture(STATE_9.c_str()),
        LoadTexture(STATE_10.c_str())
    };

}

Board::Cell& Board::GetCell(Point pos) {

    assert(pos.x >= 0 && pos.y >= 0);
    assert(pos.x < CELL_WIDTH && pos.y < CELL_HEIGHT);

    int index = CELL_WIDTH * pos.y + pos.x;

    return cells[index];
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

void Board::DrawCell(Point pos) const {

    Point cellPos = pos;

    cellPos *= CELL_SIZE;
    cellPos += SCREEN_POS;

    assert(pos.x >= 0 && pos.y >= 0);
    assert(pos.x < CELL_WIDTH && pos.y < CELL_HEIGHT);

    int index = CELL_WIDTH * pos.y + pos.x;

    DrawSprite(textures[cells[index].state], cellPos, 1);
}

void Board::OpenCell(Point pos) {
    Board::Cell& currCell = GetCell(pos);

    if (currCell.state != 0) return;

    currCell.state = 1;

    OpenCell(pos - 1);
    OpenCell(pos + 1);
    OpenCell({pos.x, pos.y + 1});
    OpenCell({pos.x, pos.y - 1});
    OpenCell({pos.x + 1, pos.y});
    OpenCell({pos.x - 1, pos.y});
    OpenCell({pos.x + 1, pos.y - 1});
    OpenCell({pos.x - 1, pos.y + 1});
}

void Board::Draw() const {

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            DrawCell({j, i});
        }
    }
}
