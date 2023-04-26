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
    SDL_Point position;
};

class Character : public GameObject {
public:
    Character(CharacterState state);
    virtual ~Character();

    virtual void updatePosition(int count) = 0;
    CharacterState getState() const;
    void setState(const CharacterState& state);
protected:
    CharacterState state;
};
