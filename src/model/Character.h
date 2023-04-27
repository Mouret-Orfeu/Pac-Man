#pragma once

#include "GameObject.h"

#include <SDL.h>

enum class CharacterDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct CharacterState {
    CharacterDirection direction;
    SDL_Point top_left_position;
    SDL_Point center_position;
};

class Character : public GameObject {
public:
    Character(CharacterState state);
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
    void updatePosition ();

    CharacterState getState() const;
    void setState(const CharacterState& state);

    CharacterDirection getDirection() const;
    void setDirection(CharacterDirection direction);

    SDL_Point getTopLeftPosition() const;
    void setTopLeftPosition(int x, int y);

    SDL_Point getCenterPosition() const;
    void setCenterPosition(int x, int y);

    SDL_Point getTilePosition() const;
    void setTilePosition(int x, int y);



protected:
    CharacterState state;
};
