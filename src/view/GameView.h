#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"

#include <SDL.h>


//On veut une fenetre de 28*36 tile
#define WINDOW_WIDTH  672
#define WINDOW_HEIGHT 864
#define MAP_WIDTH 672
#define MAP_HEIGHT 744
#define TILE_SIZE 24


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
