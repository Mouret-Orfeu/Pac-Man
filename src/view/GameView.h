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

class GameView {
public:
    GameView(GameModel& gameModel);
    ~GameView();

    void draw();

    void render(const Ghost& ghost);
    void render(const PacMan& pacman);
    void renderHUD();
    void renderMaze();

private:
    GameModel& gameModel;

    // SDL window and surfaces
    SDL_Window* pWindow = nullptr;
    SDL_Surface* win_surf = nullptr;
    SDL_Surface* spriteSheet_NES = nullptr;
    SDL_Surface* spriteSheet_Namco = nullptr;
    SDL_Surface* spriteSheet_Namco_formatted = nullptr;


    // Constants for the tile size and upscaling factor
    static constexpr int UPSCALING_FACTOR = 3;
    static constexpr int ORIGINAL_TILE_SIZE = 8;
    static constexpr int TILE_SIZE = UPSCALING_FACTOR*ORIGINAL_TILE_SIZE;

    // Constants for the window/maze dimensions
    static constexpr int MAP_COLS = 28,
                         MAP_ROWS = 36;
    static constexpr int MAZE_COLS = 28,
                         MAZE_ROWS = 31;
    static constexpr int WINDOW_WIDTH  = MAP_COLS*TILE_SIZE,
                         WINDOW_HEIGHT = MAP_ROWS*TILE_SIZE;
    static constexpr int MAZE_WIDTH  = MAZE_COLS*TILE_SIZE,
                         MAZE_HEIGHT = MAZE_ROWS*TILE_SIZE;

    // Constants for the top left corner of the maze and various sprites
    static constexpr int SIZE_LIFE_SPRITE = 11;
    static constexpr int SIZE_LIFE_SPRITE_RESIZED = UPSCALING_FACTOR*SIZE_LIFE_SPRITE;
    static constexpr SDL_Point map_top_left = {0,3*TILE_SIZE};
    static constexpr SDL_Rect map_sprite_originale = { 0,0, MAZE_COLS*ORIGINAL_TILE_SIZE,MAZE_ROWS*ORIGINAL_TILE_SIZE }; // x,y, w,h (0,0) en haut a gauche
    static constexpr SDL_Rect map_sprite_prof = { 200,3, 168,216 };
    static constexpr SDL_Rect zero_sprite = { 3,52, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect one_sprite = { 11,52, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect U_sprite = { 43,68, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect P_sprite = { 3,68, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect life_sprite = { 587,18, SIZE_LIFE_SPRITE,SIZE_LIFE_SPRITE};

    // Ghost sprites
    static constexpr int SIZE_GHOST_SPRITE = 14;
    static constexpr int SIZE_GHOST_SPRITE_RESIZED = UPSCALING_FACTOR*SIZE_GHOST_SPRITE;
    // Blinky
    // WARNING: duplicate code, editing the initial position here has no effect.
    // You need to also edit the initial position in the construct of GameModel
    // TODO: fix this by separating between the model (conceptual positions) and
    // the view (real, upscaled positions = conceptual positions * UPSCALING_FACTOR)
    static constexpr SDL_Point init_pos_up_left_Blinky = { 5*UPSCALING_FACTOR,29*UPSCALING_FACTOR };
    // The -1 is to choose the top left center pixel of the sprite. Indeed, since the
    // sprite size is even, the center is not a pixel but a square of 4 pixels.
    static constexpr SDL_Point init_pos_center_Blinky = { 5*UPSCALING_FACTOR+(SIZE_GHOST_SPRITE-1)/2*UPSCALING_FACTOR, 29*UPSCALING_FACTOR+(SIZE_GHOST_SPRITE-1)/2*UPSCALING_FACTOR };
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
    static constexpr int SIZE_PACMAN_SPRITE_RESIZED = UPSCALING_FACTOR*SIZE_PACMAN_SPRITE;
    // WARNING: duplicate code, editing the initial position here has no effect.
    // You need to also edit the initial position in the construct of GameModel
    // TODO: fix this by separating between the model (conceptual positions) and
    // the view (real, upscaled positions = conceptual positions * UPSCALING_FACTOR)
    static constexpr SDL_Point init_pos_up_left_pacman = { 106*UPSCALING_FACTOR,(3+22)*TILE_SIZE+5*UPSCALING_FACTOR };
    // Contrary to the ghost, the -1 isn't strictly necessary since SIZE_PACMAN_SPRITE is odd.
    // Still, it's better to keep it to prepare for future changes (refactoring, change of SIZE_PACMAN_SPRITE, reuse of the code, ...)
    static constexpr SDL_Point init_pos_center_pacman = { 106*UPSCALING_FACTOR+(SIZE_PACMAN_SPRITE-1)/2*UPSCALING_FACTOR, (3+22)*TILE_SIZE+5*UPSCALING_FACTOR+(SIZE_PACMAN_SPRITE-1)/2*UPSCALING_FACTOR };
    static constexpr SDL_Rect pacman_sprite_r = { 473,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_l = { 473,17, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_d = { 473,49, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_u = { 473,33, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };

    // SDL rectangles for maze and HUP elements
    SDL_Rect bg = { 0,3*TILE_SIZE, MAZE_COLS*TILE_SIZE,MAZE_ROWS*TILE_SIZE };
    SDL_Rect first_score_number_pos = { 5*TILE_SIZE,TILE_SIZE, TILE_SIZE,TILE_SIZE };
    SDL_Rect second_score_number_pos = { 6*TILE_SIZE,TILE_SIZE, TILE_SIZE,TILE_SIZE };
    SDL_Rect one_up_one_pos = { 3*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect one_up_U_pos = { 4*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect one_up_P_pos = { 5*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect first_life_pos = { 2*TILE_SIZE+UPSCALING_FACTOR*3,WINDOW_HEIGHT-2*TILE_SIZE+UPSCALING_FACTOR*2, SIZE_LIFE_SPRITE_RESIZED,SIZE_LIFE_SPRITE_RESIZED};
    SDL_Rect second_life_pos = { 4*TILE_SIZE+UPSCALING_FACTOR*3,WINDOW_HEIGHT-2*TILE_SIZE+UPSCALING_FACTOR*2, SIZE_LIFE_SPRITE_RESIZED,SIZE_LIFE_SPRITE_RESIZED };
    SDL_Rect third_life_pos = { 6*TILE_SIZE+UPSCALING_FACTOR*3,WINDOW_HEIGHT-2*TILE_SIZE+UPSCALING_FACTOR*2, SIZE_LIFE_SPRITE_RESIZED,SIZE_LIFE_SPRITE_RESIZED };

    // Constants for the map dimensions and layout
    static constexpr int MAP[MAP_ROWS][MAP_COLS] = {
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
};
