#include <raylib.h>
#include <array>
#include "point.h"

inline void DrawRect(Point pos, Point size, Color color) {

    DrawRectangle(pos.x, pos.y, size.x, size.y, color);
}

inline void DrawSprite(Texture2D texture, Point pos, float size) {

    DrawTextureEx(texture, {(float)pos.x, (float)pos.y}, 0, size, WHITE);
}

inline void DrawClock(std::array<Texture2D, 3> textures, Point pos, float size) {

    DrawRect(pos, {(int)(size * 19), (int)(size * 9)}, BLACK);

    Point indented = pos + size;

    for (int i = 0; i < 3; i++) {

        DrawSprite(textures[i], indented, size);
        
        indented.x += size * 6;
    }
}