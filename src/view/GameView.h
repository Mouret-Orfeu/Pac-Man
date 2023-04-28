#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"

#include <SDL.h>

enum class Cell {
    WALL = -1,
    EMPTY = 0,
    DOT = 1,
    POWER_PELLET = 2,
    // FRUIT = 3,
};

SDL_Point computeCenterPosition(SDL_Point top_left_position, int size);

SDL_Point computeTilePosition(SDL_Point top_left_position, int size);

SDL_Point getCoordCenterTile(SDL_Point tile_pos);

class GameView {
public:
    GameView(GameModel& gameModel);
    ~GameView();

    void draw();

    void render(const Ghost& ghost);
    void render(const PacMan& pacman);
    void renderHUD();
    void renderMaze();

    void renderSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency);

    SDL_Point getTopLeftPosition(SDL_Point position, int size);
    SDL_Point computeCenterPosition(SDL_Point top_left_position, int size);
    SDL_Point computeTilePosition(SDL_Point top_left_position, int size);
    SDL_Point getCoordCenterTile(SDL_Point tile_pos);

    // DEBUG
    void TileOutline(SDL_Surface* win_surf, SDL_Point tile_position);
    void drawAllTileOutlines();

private:
    GameModel& gameModel;

    // SDL window and surfaces
    SDL_Window* pWindow = nullptr;
    SDL_Surface* win_surf = nullptr;
    SDL_Surface* spriteSheet_NES = nullptr;
    SDL_Surface* spriteSheet_Namco = nullptr;
    SDL_Surface* spriteSheet_Namco_formatted = nullptr;

    // Upscaling factor
    static constexpr int UPSCALING_FACTOR = 3;

    // Tile size
    static constexpr int TILE_SIZE = GameModel::TILE_SIZE;

    // Window dimensions
    static constexpr int WINDOW_WIDTH  = UPSCALING_FACTOR*GameModel::WIDTH,
                         WINDOW_HEIGHT = UPSCALING_FACTOR*GameModel::HEIGHT;

    // Map sprites
    static constexpr SDL_Rect maze_Namco = { 0,0, GameModel::MAZE_COLS*TILE_SIZE,GameModel::MAZE_ROWS*TILE_SIZE }; // x,y, w,h (0,0) en haut a gauche
    static constexpr SDL_Rect maze_NES = { 200,3, 168,216 };

    // HUP sprites
    static constexpr SDL_Rect zero_sprite = { 3,52, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect one_sprite = { 11,52, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect U_sprite = { 43,68, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect P_sprite = { 3,68, TILE_SIZE,TILE_SIZE };
    static constexpr int SIZE_LIFE_SPRITE = 11;
    static constexpr SDL_Rect life_sprite = { 587,18, SIZE_LIFE_SPRITE,SIZE_LIFE_SPRITE};

    static constexpr int SIZE_GHOST_SPRITE = 14;
    // Ghost sprites
    // Blinky
    static constexpr SDL_Rect Blinky_sprite_r = { 457,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Blinky_sprite_l = { 489,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Blinky_sprite_d = { 553,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Blinky_sprite_u = { 521,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    // Pinky
    // ...
    // Inky
    // ...
    // Clyde
    // ...

    // PacMan sprites
    static constexpr int SIZE_PACMAN_SPRITE = 13;
    static constexpr SDL_Rect pacman_sprite_r = { 473,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_l = { 473,17, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_d = { 473,49, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_u = { 473,33, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
};
