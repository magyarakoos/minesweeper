#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
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
    Construct();
}

void Board::Construct() {
    assert(CELL_WIDTH > 0 && CELL_HEIGHT > 0);
    assert(CELL_SIZE > 0);

    cells.resize(0);
    cells.resize(CELL_WIDTH * CELL_HEIGHT);

    gameStarted = 0;

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
        LoadTexture(STATE_10.c_str()),
        LoadTexture(STATE_11.c_str())
    };
}

int Board::AsIndex(Point pos) const {

    assert(pos.x >= 0 && pos.y >= 0);
    assert(pos.x < CELL_WIDTH && pos.y < CELL_HEIGHT);

    return CELL_WIDTH * pos.y + pos.x;
}

Board::Cell& Board::GetCell(Point pos) {

    return cells[AsIndex(pos)];
}

const Board::Cell& Board::GetCellConst(Point pos) const {

    return cells[AsIndex(pos)];
}

void Board::SetCell(Point pos, Color c) {

    cells[AsIndex(pos)].SetColor(c);
}

Color Board::GetColor(Point pos) const {

    return cells[AsIndex(pos)].color;
}

void Board::DrawCell(Point pos) const {

    Point cellPos = pos;

    cellPos *= CELL_SIZE;
    cellPos += SCREEN_POS;

    Texture2D texture = textures[cells[AsIndex(pos)].state];

    DrawSprite(texture, cellPos, (float)CELL_SIZE / 32);
}

void Board::SetBombs(Point start) {

    std::vector<Point> bombPos;

    while (bombPos.size() != BOMB_COUNT) {
            
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

    std::cerr << "SETBOMBS " << bombPos.size() << '\n';
    for (Point p : bombPos) {
        std::cerr << p.x << ' ' << p.y << '\n';
    }
    std::cerr << '\n';

    for (Point p : bombPos) {
        Board::Cell& currCell = GetCell(p);

        currCell.isBomb = 1;
    }
}

int Board::BombsAround(Point pos) const {
    
    const Board::Cell& currCell = GetCellConst(pos);

    if (currCell.isBomb) {
        return 9;
    }

    int result = 0;

    for (Point dir : DIRS) {
        
        Point p = pos + dir;

        result += (
            p.x >= 0 && p.y >= 0 && 
            p.x < CELL_WIDTH && p.y < CELL_HEIGHT &&
            GetCellConst(p).isBomb
        );
    }

    return result;
}

int Board::FlagsAround(Point pos) const {

    const Board::Cell& currCell = GetCellConst(pos);

    int result = 0;

    for (Point dir : DIRS) {
        
        Point p = pos + dir;

        result += (
            p.x >= 0 && p.y >= 0 && 
            p.x < CELL_WIDTH && p.y < CELL_HEIGHT &&
            GetCellConst(p).state == 11
        );
    }

    return result;
}

void Board::ZeroSpread(Point pos) {
    
    std::vector<bool> vis(CELL_WIDTH * CELL_HEIGHT);

    std::queue<Point> todo;

    todo.push(pos);
    vis[AsIndex(pos)] = 1;

    while (!todo.empty()) {
        Point p = todo.front(); 
        todo.pop();

        Board::Cell& currCell = GetCell(p);
        
        int bombs = BombsAround(p);

        currCell.state = (bombs == 0 ? 10 : bombs);

        if (bombs == 0) {
            std::cerr << "EMPTYCALL " << p.x << ' ' << p.y << '\n';
            currCell.state = 10;

            for (Point dir : DIRS) {
                Point newPos = p + dir;


                if (newPos.x >= 0 && newPos.y >= 0 && 
                    newPos.x < CELL_WIDTH && newPos.y < CELL_HEIGHT && 
                    !vis[AsIndex(newPos)]
                    ) {
                
                    vis[AsIndex(newPos)] = 1;
                    todo.push(newPos);

                    std::cerr << "PUSHCALL " << newPos.x << ' ' << newPos.y << '\n';
                }
            }
        }
        else {
            std::cerr << "STATECALL " << p.x << ' ' << p.y << ' ' << bombs << '\n';
            currCell.state = bombs;
        }
    }
}

int Board::ToggleFlag(Point pos) {

    Board::Cell& currCell = GetCell(pos);

    if (currCell.state == 0) {
        currCell.state = 11;
        return -1;
    }

    if (currCell.state == 11) {
        currCell.state = 0;
        return 1;
    }

    return 0;
}

int Board::FlagBasedAutoOpen(Point pos) {

    Board::Cell& currCell = GetCell(pos);

    if (currCell.state < 1 || currCell.state > 8) {
        return 0;
    }

    int flags = FlagsAround(pos);
    std::cerr << "FLAGS " << flags << '\n';

    if (flags != currCell.state) {
        return 0;
    }

    for (Point dir : DIRS) {
        Point newPos = pos + dir;

        if (newPos.x >= 0 && newPos.y >= 0 && 
            newPos.x < CELL_WIDTH && newPos.y < CELL_HEIGHT
            ) {
        
            Board::Cell& neighCell = GetCell(newPos);

            if (neighCell.state == 11) {
                continue;
            }

            if (neighCell.isBomb) {
                return 1;
            }

            int bombs = BombsAround(newPos);

            neighCell.state = bombs;

            if (bombs != 0) {
                continue;
            }

            ZeroSpread(newPos);
        }
    }

    return 0;
}

int Board::OpenCell(Point pos) {

    Board::Cell& currCell = GetCell(pos);

    if (currCell.state != 0) {
        std::cerr << "FLAGOPEN CALL " << currCell.state << ' ' << pos.x << ' ' << pos.y << '\n';
        return FlagBasedAutoOpen(pos);
    }
        
    int bombs = BombsAround(pos);

    currCell.state = bombs;

    if (currCell.isBomb) {
        return 1;
    }

    if (bombs != 0) {
        return 0;
    }

    ZeroSpread(pos);

    return 0;
}

void Board::Draw() const {

    for (int i = 0; i < CELL_HEIGHT; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) {

            DrawCell({j, i});
        }
    }
}
