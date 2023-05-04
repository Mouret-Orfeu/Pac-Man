#pragma once

#include "common/Direction.h"
#include "Tile.h"

#include <SDL.h>

class Position {
public:
    enum class CoordinateSystem {
        CENTER,
        TOP_LEFT
    };

    Position(int x, int y, CoordinateSystem coordinateSystem = CoordinateSystem::CENTER);
    Position(const SDL_Point& point, CoordinateSystem coordinateSystem = CoordinateSystem::CENTER);
    Position(Tile tile);

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    bool operator==(const Position& other) const;

    Position& operator+=(const SDL_Point& point);
    Position& operator-=(const SDL_Point& point);

    Position operator+(const SDL_Point& point) const;
    Position operator-(const SDL_Point& point) const;

    void incrementX(int value);
    void incrementY(int value);

    SDL_Point toCenter() const;
    Tile toTile() const;

    /**
    * @brief On va prendre le pixel en haut à gauche du cerré central de la tile correspondante à la position
    *
    */
    SDL_Point getTileCenter() const;

    Tile getTilePosition() const;
    void setTilePosition( Tile& tile_position);

    SDL_Point toTopLeft() const;
    Tile getNextTile(const Direction& direction) const;
    bool isCenteredHorizontallyOnTile() const;
    bool isCenteredVerticallyOnTile() const;
    bool isCenteredOnTile() const;

    int distance_tile(Tile& t1, Tile& t2) const;

    bool operator==(const Tile& T2) const;



private:
    //centre de PacMan
    SDL_Point center_position;
    
};

Position operator+(const Position& pos, const SDL_Point& point);
