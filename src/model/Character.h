#pragma once

#include "GameObject.h"
#include "common/GameDimensions.h"
#include "common/Tile.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <string.h>

#include <SDL.h>

class GameModel;

class Character : public GameObject {
public:
    Character(GameModel& game_model, Position spawn_position, Direction spawn_direction);
    virtual ~Character();

    void reset();

    /**
    * @brief Traite la logique de déplacement des personnages et met à jour leur position
    *
    */
    virtual void move() = 0;

    /**
    * @brief Sous fonction de move, ne sert qu'à changer top_left_position et center_position en fonction de la direction calculée dans move
    *
    */
    virtual void updatePosition();

    virtual void updateDirection() = 0;


    Position getPosition() const;
    void setPosition(Position position);

    Direction getDirection() const;
    void setDirection(Direction direction);

    //DEBUG
    void printDirection(Direction d) const;

    Position getSpawnPos() const;

    virtual void die() =0;

    void setFramesToDrop(int frames);

protected:
    GameModel& game_model;
    const Position spawn_position;
    Position position;
    Direction direction;
    const Direction spawn_direction;
    int frames_to_drop;

    //static constexpr Tile TELEPORTATION_TILE_RIGHT(3+(MAZE_ROWS/2)-1, MAZE_COLS-1);
    //static constexpr Tile TELEPORTATION_TILE_LEFT(3+(MAZE_ROWS/2)-1, 0);

    Tile TELEPORTATION_TILE_RIGHT;
    Tile TELEPORTATION_TILE_LEFT;
};
