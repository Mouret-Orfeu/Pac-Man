#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"

#include <SDL.h>

class GameView {
public:
    GameView(GameModel& gameModel);
    ~GameView();

    void draw();

    void render(const Ghost& ghost);

private:
    SDL_Surface* win_surf;
    SDL_Surface* plancheSprites;
    GameModel& gameModel;
    // ... Other private members ...
};
