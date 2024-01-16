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

    #pragma region Point + Point operators
    bool operator==(Point p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(Point p) const {
        return !(*this == p);
    }

    Point operator+(Point p) const {
        return {
            x + p.x,
            y + p.y
        };
    }

    Point& operator+=(Point p) {
        return *this = *this + p;
    }

    Point operator-(Point p) const {
        return {
            x - p.x,
            y - p.y
        };
    }

    Point& operator-=(Point p) {
        return *this = *this - p;
    }

    Point operator*(Point p) const {
        return {
            x * p.x,
            y * p.y
        };
    }

    Point& operator*=(Point p) {
        return *this = *this * p;
    }
#pragma endregion

    #pragma region Point + Scalar operators
    bool operator==(int n) const {
        return x == n && y == n;
    }

    bool operator!=(int n) const {
        return !(*this == n);
    }

    Point operator+(int n) const {
        return {
            x + n,
            y + n
        };
    }

    Point& operator+=(int n) {
        return *this = *this + n;
    }

    Point operator-(int n) const {
        return {
            x - n,
            y - n
        };
    }

    Point& operator-=(int n) {
        return *this = *this - n;
    }

    Point operator*(int n) const {
        return {
            x * n,
            y * n
        };
    }

    Point& operator*=(int n) {
        return *this = *this * n;
    }
#pragma endregion

};
