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

namespace GameViewConstants {

    // Upscaling factor
    static constexpr int UPSCALING_FACTOR = 3;

    // Constants for the window/maze dimensions
    static constexpr int TILE_SIZE = 8;
    static constexpr int COLS = 28,
                         ROWS = 36;
    static constexpr int MAZE_COLS = 28,
                         MAZE_ROWS = 31;
    static constexpr int WIDTH  = COLS*TILE_SIZE,
                         HEIGHT = ROWS*TILE_SIZE;
    static constexpr int WINDOW_WIDTH  = UPSCALING_FACTOR*WIDTH,
                         WINDOW_HEIGHT = UPSCALING_FACTOR*HEIGHT;

    // Ghost sprites
    static constexpr int SIZE_GHOST_SPRITE = 14;
    // Blinky
    // The -1 is to choose the top left center pixel of the sprite. Indeed, since the
    // sprite size is even, the center is not a pixel but a square of 4 pixels.
    static constexpr SDL_Point init_pos_center_Blinky = { 5+(SIZE_GHOST_SPRITE-1)/2, 29+(SIZE_GHOST_SPRITE-1)/2 };

    // PacMan sprites
    static constexpr int SIZE_PACMAN_SPRITE = 13;
    // Contrary to the ghost, the -1 isn't strictly necessary since SIZE_PACMAN_SPRITE is odd.
    // Still, it's better to keep it to prepare for future changes (refactoring, change of SIZE_PACMAN_SPRITE, reuse of the code, ...)
    static constexpr SDL_Point init_pos_center_pacman = { 106+(SIZE_PACMAN_SPRITE-1)/2, (3+22)*TILE_SIZE+5+(SIZE_PACMAN_SPRITE-1)/2 };



    // Constants for the map dimensions and layout
    static constexpr int TILES[ROWS][COLS] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
        {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
        {-1, 2,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 2,-1},
        {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
        {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
        {-1, 1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
        {-1, 1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
        {-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 0,-1,-1, 0,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 0,-1,-1, 0,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
        {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
        {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
        {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
        {-1, 2, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 2,-1},
        {-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1},
        {-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1},
        {-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1,-1},
        {-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1},
        {-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1},
        {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };


}

using namespace GameViewConstants;

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

    // Constants for the top left corner of the maze and various sprites
    static constexpr int SIZE_LIFE_SPRITE = 11;
    static constexpr int SIZE_LIFE_SPRITE_RESIZED = UPSCALING_FACTOR*SIZE_LIFE_SPRITE;
    static constexpr SDL_Rect map_sprite_originale = { 0,0, MAZE_COLS*TILE_SIZE,MAZE_ROWS*TILE_SIZE }; // x,y, w,h (0,0) en haut a gauche
    static constexpr SDL_Rect map_sprite_prof = { 200,3, 168,216 };
    static constexpr SDL_Rect zero_sprite = { 3,52, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect one_sprite = { 11,52, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect U_sprite = { 43,68, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect P_sprite = { 3,68, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect life_sprite = { 587,18, SIZE_LIFE_SPRITE,SIZE_LIFE_SPRITE};


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
    static constexpr SDL_Rect pacman_sprite_r = { 473,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_l = { 473,17, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_d = { 473,49, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_u = { 473,33, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
};
