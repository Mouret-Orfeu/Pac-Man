#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <SDL.h>

class GameModel;

class Ghost : public Character {
public:
    enum class Type {
        BLINKY,
        PINKY,
        INKY,
        CLYDE
    };

    enum class Mode {
        SCATTER,
        CHASE,
        FRIGHTENED
    };

    Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation);
    Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile);
    virtual ~Ghost();

    Type getType() const;

    Mode getMode() const;

    void setChaseTargetTile(Tile tile);
    Tile getScatterTargetTile() const;

private:
    Type ghost_type;
    Mode ghost_mode=Mode::SCATTER;

    Tile scatter_target_tile;
    Tile chase_target_tile;

    Tile current_target_tile=scatter_target_tile;
};
