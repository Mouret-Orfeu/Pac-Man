#include "Position.h"
#include "Direction.h"
#include "GameDimensions.h"
#include "model/GameModel.h"
#include "model/Character.h" // TODO: Put Direction in common/Direction.h

Position::Position(int x, int y, CoordinateSystem coordinateSystem) {
    switch (coordinateSystem) {
        case CoordinateSystem::CENTER:
            centerPosition = {x, y};
            break;
        case CoordinateSystem::TOP_LEFT:
            centerPosition = {x + (SPRITE_SIZE-1) / 2, y + (SPRITE_SIZE-1) / 2};
            break;
    }
}

Position::Position(const SDL_Point& point, CoordinateSystem coordinateSystem)
: Position(point.x, point.y, coordinateSystem) {}

Position::Position(Tile tile) {
    centerPosition = {tile.j * 8 + (TILE_SIZE-1) / 2, tile.i * 8 + (TILE_SIZE-1) / 2};
}

int Position::getX() const {
    SDL_Point point = toCenter();
    return point.x;
}

int Position::getY() const {
    SDL_Point point = toCenter();
    return point.y;
}

void Position::setX(int x) {
    centerPosition.x = x;
}

void Position::setY(int y) {
    centerPosition.y = y;
}

// equality operator
bool Position::operator==(const Position& other) const {
    return centerPosition.x == other.centerPosition.x && centerPosition.y == other.centerPosition.y;
}

Position& Position::operator+=(const SDL_Point& point) {
    setX(getX() + point.x);
    setY(getY() + point.y);
    return *this;
}

Position& Position::operator-=(const SDL_Point& point) {
    setX(getX() - point.x);
    setY(getY() - point.y);
    return *this;
}

Position Position::operator+(const SDL_Point& point) const {
    Position result(*this);
    result += point;
    return result;
}

Position Position::operator-(const SDL_Point& point) const {
    Position result(*this);
    result -= point;
    return result;
}

void Position::incrementX(int value) {
    setX(getX() + value);
}

void Position::incrementY(int value) {
    setY(getY() + value);
}

SDL_Point Position::toCenter() const {
    return centerPosition;
}

Tile Position::toTile() const {
    return {centerPosition.y / 8, centerPosition.x / 8};
}

SDL_Point Position::toTopLeft() const {
    return {centerPosition.x - (SPRITE_SIZE-1) / 2, centerPosition.y - (SPRITE_SIZE-1) / 2};
}

Tile Position::getNextTile(const Direction& direction) const {
    Tile tile = toTile();
    switch (direction) {
        case Direction::UP:
            tile.i -= 1;
            break;
        case Direction::DOWN:
            tile.i += 1;
            break;
        case Direction::LEFT:
            tile.j -= 1;
            break;
        case Direction::RIGHT:
            tile.j += 1;
            break;
        case Direction::NONE:
            break;
    }
    return tile;
}

bool Position::isCenteredHorizontallyOnTile() const {
    const int offsetX = centerPosition.x % 8;
    return offsetX == 3;
}

bool Position::isCenteredVerticallyOnTile() const {
    const int offsetY = centerPosition.y % 8;
    return offsetY == 3;
}

bool Position::isCenteredOnTile() const {
    const int offsetX = centerPosition.x % 8;
    const int offsetY = centerPosition.y % 8;
    return isCenteredHorizontallyOnTile() && isCenteredVerticallyOnTile();
}
