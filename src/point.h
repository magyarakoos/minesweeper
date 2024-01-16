#pragma once

struct Point {
private:
    int x;
    int y;

public:
    Point() = default;
    Point(int _x, int _y) : x(_x), y(_y) {}

    int GetX() const { return x; }
    int GetY() const { return y; }

    void SetX(int _x) { x = _x; }
    void SetY(int _y) { y = _y; }

    bool operator==(Point p) {
        return x == p.x && y == p.y;
    }

    bool operator!=(Point p) {
        return !(*this == p);
    }

    Point operator+(Point p) {
        return {
            x + p.x,
            y + p.y
        };
    }

    Point& operator+=(Point p) {
        return *this = *this + p;
    }

    Point operator-(Point p) {
        return {
            x - p.x,
            y - p.y
        };
    }

    Point& operator-=(Point p) {
        return *this = *this - p;
    }

    Point operator*(Point p) {
        return {
            x * p.x,
            y * p.y
        };
    }

    Point& operator*=(Point p) {
        return *this = *this * p;
    }
};