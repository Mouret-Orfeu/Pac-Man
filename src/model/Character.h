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
    Character(GameModel& gameModel, Position initial_position, Direction direction, Direction sprite_orientation);
    Character(GameModel& gameModel, Position initial_position, Direction direction);
    virtual ~Character();

    /**
    * @brief Traite la logique de déplacement des personnages et met à jour leur position
    *
    * @param count est un compteur qui sert pour l'instant à boucler le mouvement du fantome
    */
    virtual void move(const int count) = 0;

    /**
    * @brief Sous fonction de move, ne sert qu'à changer top_left_position et center_position en fonction de la direction calculée dans move
    *
    *
    */
    virtual void updatePosition();

    virtual void updateDirection() = 0;


    Position getPosition() const;
    void setPosition(Position position);

    Direction getDirection() const;
    void setDirection(Direction direction);

    Direction getSpriteOrientation() const;
    void setSpriteOrientation(Direction sprite_orientation);

    //DEBUG
    void printDirection() const;

protected:
    GameModel& gameModel;
    const Position initial_position;
    Position position;
    Direction direction;
    Direction sprite_orientation;
    int frames_to_drop;

    //static constexpr Tile TELEPORTATION_TILE_RIGHT(3+(MAZE_ROWS/2)-1, MAZE_COLS-1);
    //static constexpr Tile TELEPORTATION_TILE_LEFT(3+(MAZE_ROWS/2)-1, 0);

    Tile TELEPORTATION_TILE_RIGHT;
    Tile TELEPORTATION_TILE_LEFT;
};
