#pragma once

struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {}
    constexpr Point(int _x, int _y) : x(_x), y(_y) {}

    #pragma region Point + Point operators
    constexpr bool operator==(Point p) const {
        return x == p.x && y == p.y;
    }

    constexpr bool operator!=(Point p) const {
        return !(*this == p);
    }

    constexpr Point operator+(Point p) const {
        return {
            x + p.x,
            y + p.y
        };
    }

    constexpr Point& operator+=(Point p) {
        return *this = *this + p;
    }

    constexpr Point operator-(Point p) const {
        return {
            x - p.x,
            y - p.y
        };
    }

    constexpr Point& operator-=(Point p) {
        return *this = *this - p;
    }

    constexpr Point operator*(Point p) const {
        return {
            x * p.x,
            y * p.y
        };
    }

    constexpr Point& operator*=(Point p) {
        return *this = *this * p;
    }
#pragma endregion

    #pragma region Point + Scalar operators
    constexpr bool operator==(int n) const {
        return x == n && y == n;
    }

    constexpr bool operator!=(int n) const {
        return !(*this == n);
    }

    constexpr Point operator+(int n) const {
        return {
            x + n,
            y + n
        };
    }

    constexpr Point& operator+=(int n) {
        return *this = *this + n;
    }

    constexpr Point operator-(int n) const {
        return {
            x - n,
            y - n
        };
    }

    constexpr Point& operator-=(int n) {
        return *this = *this - n;
    }

    constexpr Point operator*(int n) const {
        return {
            x * n,
            y * n
        };
    }

    constexpr Point& operator*=(int n) {
        return *this = *this * n;
    }
#pragma endregion

};
