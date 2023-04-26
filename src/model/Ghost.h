#pragma once

#include "GameObject.h"

#include <SDL.h>

enum class GhostDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct GhostState {
    GhostDirection direction;
    SDL_Point position;
};

class Ghost : public GameObject {
public:
    Ghost();
    ~Ghost();

    void updatePosition(int count);
    GhostState getState() const;
    void setState(const GhostState& state);
    const SDL_Rect& getSpriteR() const;
    const SDL_Rect& getSpriteL() const;
    const SDL_Rect& getSpriteD() const;
    const SDL_Rect& getSpriteU() const;
private:
    GhostState state;
    const SDL_Rect sprite_r;
    const SDL_Rect sprite_l;
    const SDL_Rect sprite_d;
    const SDL_Rect sprite_u;
};
