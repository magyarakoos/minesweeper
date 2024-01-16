#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "random_between.h"
#include "point.h"
#include "board.h"
#include "settings.h"
#include "graphics.h"

Board::Cell::Cell()
    :
    state(0),
    isBomb(0),
    color(WHITE) {}

void Board::Cell::SetColor(Color c) {
    color = c;
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

void Board::SetBombs(Point start) {

    int bombCount = std::max(CELL_WIDTH, CELL_HEIGHT);
    std::vector<Point> bombPos;

    while (bombPos.size() != bombCount) {
            
        Point p {
            random_between(0, CELL_WIDTH - 1),
            random_between(0, CELL_HEIGHT - 1)
        };

        if (p != start && 
            std::find(bombPos.begin(), bombPos.end(), p) == bombPos.end()
            ) {

            bombPos.push_back(p);
        }
    }

    for (Point p : bombPos) {
        Board::Cell& currCell = GetCell(p);

        currCell.isBomb = 1;
    }
}

int Board::BombsArount(Point pos) {
    
    if (GetCell(pos).isBomb) {
        return -1;
    }

    int result = 0;

    for (Point dir : DIRS) {
        
        Point p = pos + dir;

        result += (
            p.x >= 0 && p.y >= 0 && 
            p.x < CELL_WIDTH && p.y < CELL_HEIGHT &&
            GetCell(p).isBomb
        );
    }

    return result;
}

void Board::OpenCell(Point pos) {
    Board::Cell& currCell = GetCell(pos);

    if (currCell.state != 0) return;

    int bombs = BombsArount(pos);

    currCell.state = (
        bombs == -1 ? 9 : 
        bombs ==  0 ? 10 :
        bombs
    );

    if (currCell.state != 10) return;

    for (Point dir : DIRS) {
        Point newPos = pos + dir;

        if (newPos.x >= 0 && newPos.y >= 0 && newPos.x < CELL_WIDTH && newPos.y < CELL_HEIGHT) {
        
            OpenCell(pos + dir);
        }
    }
}

void Board::Draw() const {

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            DrawCell({j, i});
        }
    }
}
