#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"

#include <SDL.h>


//les vrais dimensions sont 224x288 avec des tile de taille 8 mais on double pour plus de visibilité
#define WINDOW_WIDTH  448
#define WINDOW_HEIGHT 576
#define TILE_SIZE 16


class GameView {
public:
    GameView(GameModel& gameModel);
    ~GameView();

    void draw();

    void render(const Ghost& ghost);
    void render(const PacMan& pacman);

private:
    SDL_Surface* win_surf;
    SDL_Surface* plancheSprites;
    GameModel& gameModel;
    // ... Other private members ...
};
