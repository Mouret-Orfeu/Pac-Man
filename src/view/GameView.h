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
    void draw_death(int death_sprite_count);

    void render(const Ghost& ghost);
    void render(const PacMan& pacman);
    void renderHUD();
    void renderMaze();

    void drawScore(int score, bool highscore);
    void drawText();
    void drawLives(int lives);

    void displayPacmanDeath(int death_frame);

    void renderSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency);

    SDL_Point getTopLeftPosition(SDL_Point position, int size);
    SDL_Point computeCenterPosition(SDL_Point top_left_position, int size);
    SDL_Point computeTilePosition(SDL_Point top_left_position, int size);
    SDL_Point getCoordCenterTile(SDL_Point tile_pos);

    // DEBUG
    void TileOutline(SDL_Surface* win_surf, SDL_Point tile_position);
    void drawAllTileOutlines();
    void isTileLegalAllTiles();

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

    // Other constants
    static constexpr int MAX_SCORE_DIGITS = 7;

    // HUP sprites
    static constexpr int SIZE_LIFE_SPRITE = 11;
    static constexpr SDL_Rect life_sprite = { 587,18, SIZE_LIFE_SPRITE,SIZE_LIFE_SPRITE};
    static constexpr SDL_Rect zero_sprite = { 3,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect one_sprite = { 12,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect two_sprite = { 19,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect three_sprite = { 27,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect four_sprite = { 35,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect five_sprite = { 43,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect six_sprite = { 51,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect seven_sprite = { 59,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect eight_sprite = { 67,53, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect nine_sprite = { 75,53, TILE_SIZE,TILE_SIZE };


    static constexpr SDL_Rect U_sprite = { 44,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect P_sprite = { 4,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect H_sprite = { 67,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect I_sprite = { 76,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect G_sprite = { 59,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect C_sprite = { 27,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect O_sprite = { 123,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect E_sprite = { 43,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect R_sprite = { 19,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect S_sprite = { 27,69, TILE_SIZE,TILE_SIZE };



    static constexpr int SIZE_GHOST_SPRITE = 14;
    // Ghost sprites
    // Blinky
    static constexpr SDL_Rect Blinky_sprite_r = { 457,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Blinky_sprite_l = { 489,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Blinky_sprite_d = { 553,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Blinky_sprite_u = { 521,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    // Pinky
    static constexpr SDL_Rect Pinky_sprite_r = { 457,81, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Pinky_sprite_l = { 489,81, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Pinky_sprite_d = { 553,81, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Pinky_sprite_u = { 521,81, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    // Inky
    static constexpr SDL_Rect Inky_sprite_r = { 457,97, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Inky_sprite_l = { 489,97, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Inky_sprite_d = { 553,97, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Inky_sprite_u = { 521,97, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    // Clyde
    static constexpr SDL_Rect Clyde_sprite_r = { 457,113, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Clyde_sprite_l = { 489,113, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Clyde_sprite_d = { 553,113, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };
    static constexpr SDL_Rect Clyde_sprite_u = { 521,113, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE };

    // PacMan sprites
    static constexpr int SIZE_PACMAN_SPRITE = 13;
    static constexpr SDL_Rect pacman_sprite_r = { 473,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_l = { 473,17, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_d = { 473,49, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_u = { 473,33, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_full = { 489,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };

    // PacMan death sprites
    static constexpr SDL_Rect pacman_death_sprite_1 = { 503,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_2 = { 520,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_3 = { 536,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_4 = { 552,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_5 = { 568,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_6 = { 584,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_7 = { 600,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_8 = { 616,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_9 = { 632,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_10 = { 648,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_death_sprite_11 = { 664,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE  };
};
