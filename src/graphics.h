#include <raylib.h>
#include "point.h"

inline void DrawRect(Point pos, Point size, Color color) {

    DrawRectangle(pos.x, pos.y, size.x, size.y, color);
}

inline void DrawSprite(Texture2D texture, Point pos, float size) {

    DrawTextureEx(texture, {(float)pos.x, (float)pos.y}, 0, size, {0, 0, 0, 0});
}
