#pragma once

#include "GameObject.h"
#include "common/Position.h"
#include "common/Direction.h"

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
    void updatePosition();


    Position getPosition() const;
    void setPosition(Position position);

    Direction getDirection() const;
    void setDirection(Direction direction);

    Direction getSpriteOrientation() const;
    void setSpriteOrientation(Direction sprite_orientation);

protected:
    GameModel& gameModel;
    const Position initial_position;
    Position position;
    Direction direction;
    Direction sprite_orientation;
};
