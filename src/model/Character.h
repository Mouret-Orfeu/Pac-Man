#pragma once

#include "GameObject.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"

#include <SDL.h>

class Character : public GameObject {
public:
    Character(Position position, Direction direction, Direction sprite_orientation);
    Character(Position position, Direction direction);
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
    void updatePosition();


    Position getPosition() const;
    void setPosition(Position position);

    Direction getDirection() const;
    void setDirection(Direction direction);

    Direction getSpriteOrientation() const;
    void setSpriteOrientation(Direction sprite_orientation);

    Tile getTeleportationTileRight() const;
    
    Tile getTeleportationTileLeft() const;

protected:
    Position position;
    Direction direction;
    Direction sprite_orientation;

    static constexpr Tile TELEPORTATION_TILE_RIGHT = {3+(MAZE_ROWS/2)-1, MAZE_COLS-1};
    static constexpr Tile TELEPORTATION_TILE_LEFT = {3+(MAZE_ROWS/2)-1, 0};
};
