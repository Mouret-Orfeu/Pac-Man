#include "Position.h"
#include "GameDimensions.h"

Position::Position(int x, int y, CoordinateSystem coordinateSystem) {
    switch (coordinateSystem) {
        case CoordinateSystem::CENTER:
            centerPosition = {x, y};
            break;
        case CoordinateSystem::TILE:
            centerPosition = {x * 8 + 3, y * 8 + 3};
            break;
        case CoordinateSystem::TOP_LEFT:
            centerPosition = {x + (SPRITE_SIZE / 2 - 1), y + (SPRITE_SIZE / 2 - 1)};
            break;
    }
}

Position::Position(const SDL_Point& point, CoordinateSystem coordinateSystem)
    : Position(point.x, point.y, coordinateSystem) {}

SDL_Point Position::toCenter() const {
    return centerPosition;
}

SDL_Point Position::toTile() const {
    return {centerPosition.y / 8, centerPosition.x / 8};
}

SDL_Point Position::toTopLeft() const {
    return {centerPosition.x - (SPRITE_SIZE / 2 - 1), centerPosition.y - (SPRITE_SIZE / 2 - 1)};
}
