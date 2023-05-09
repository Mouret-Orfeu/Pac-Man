#pragma once

#include "common/GameDimensions.h"
#include "common/Tile.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <string.h>

#include <SDL.h>

class GameModel;

class Character {
public:
    Character(GameModel& game_model, Position spawn_position, Direction spawn_direction);
    virtual ~Character();

    void reset();

    /**
    * @brief Traite la logique de déplacement des personnages et met à jour leur position
    *
    */
    virtual void move() =0;

    bool should_move();

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

    void printDirection(Direction d) const;

    Position getSpawnPos() const;

    virtual void die() =0;

    void setFramesToDrop(int frames);

    // setter and getter for speed
    int getSpeed() const;
    void setSpeed(int speed);

    void resetSpeedORigin();

    Uint64 getNbAnimatedFramesSinceLastSpeedChange() const;

protected:
    GameModel& game_model;
    const Position spawn_position;
    Position position;
    Direction direction;
    const Direction spawn_direction;
    int frames_to_drop;
    Uint64 nb_animated_frames_since_last_speed_change;
    Uint64 frame_count_at_last_speed_change;
    int speed; // as a percentage of the max speed, i.e. 1 pixel per frame

    const Tile TELEPORTATION_TILE_RIGHT;
    const Tile TELEPORTATION_TILE_LEFT;
};
