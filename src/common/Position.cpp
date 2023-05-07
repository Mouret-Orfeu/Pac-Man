#include "Position.h"
#include "Direction.h"
#include "GameDimensions.h"
#include "Tile.h"
#include "model/GameModel.h"
#include "model/Character.h" // TODO: Put Direction in common/Direction.h

#include <cmath>

Position::Position(int x, int y, CoordinateSystem coordinateSystem) {
    switch (coordinateSystem) {
        case CoordinateSystem::CENTER:
            center_position = {x, y};
            break;
        case CoordinateSystem::TOP_LEFT:
            center_position = {x + (SPRITE_SIZE-1) / 2, y + (SPRITE_SIZE-1) / 2};
            break;
    }
}

Position::Position(const SDL_Point& point, CoordinateSystem coordinateSystem)
: Position(point.x, point.y, coordinateSystem) {}

Position::Position(Tile tile) {
    center_position = {tile.j * 8 + (TILE_SIZE-1) / 2, tile.i * 8 + (TILE_SIZE-1) / 2};
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
    center_position.x = x;
}

void Position::setY(int y) {
    center_position.y = y;
}

// equality operator
bool Position::operator==(const Position& other) const {
    return center_position.x == other.center_position.x && center_position.y == other.center_position.y;
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
    return center_position;
}

Tile Position::toTile() const {
    return {center_position.y / 8, center_position.x / 8};
}

SDL_Point Position::getTileCenter() const
{
    SDL_Point centerTile={center_position.x/8*(TILE_SIZE)+3, center_position.y/8*(TILE_SIZE)+3};
    return centerTile;
}

SDL_Point Position::toTopLeft() const {
    return {center_position.x - (SPRITE_SIZE-1) / 2, center_position.y - (SPRITE_SIZE-1) / 2};
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
    const int offsetX = center_position.x % 8;
    return offsetX == 3;
}

bool Position::isCenteredVerticallyOnTile() const {
    const int offsetY = center_position.y % 8;
    return offsetY == 3;
}

bool Position::isCenteredOnTile() const {
    const int offsetX = center_position.x % 8;
    const int offsetY = center_position.y % 8;
    return isCenteredHorizontallyOnTile() && isCenteredVerticallyOnTile();
}

int Position::distanceTile(Tile& t1, Tile& t2) const
{
    return abs(t1.i-t2.i)+abs(t1.j-t2.j);
}

int Position::distancePosition(const Position& p2) const
{
    return abs(getX()-p2.getX())+abs(getY()-p2.getY());
}