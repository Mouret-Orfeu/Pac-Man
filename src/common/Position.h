#pragma once

#include <SDL.h>

class Position {
public:
    enum class CoordinateSystem {
        CENTER,
        TILE,
        TOP_LEFT
    };

    Position(int x, int y, CoordinateSystem coordinateSystem);
    Position(const SDL_Point& point, CoordinateSystem coordinateSystem);

    SDL_Point toCenter() const;
    SDL_Point toTile() const;
    SDL_Point toTopLeft() const;

private:
    SDL_Point centerPosition;
};
