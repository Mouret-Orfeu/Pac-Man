#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"

#include <SDL.h>


class GameView {
public:
    GameView(GameModel& gameModel);
    ~GameView();

    void draw();
    void drawDeathAnimation(int death_sprite_count);

    void drawGhost(const Ghost& ghost);
    void drawPacMan(const PacMan& pacman);

    void drawHUD();
    void drawMaze();

    void drawScore(int score, bool highscore);
    void drawText();
    void drawLives(int lives);

    void drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency);
    // DEBUG
    void drawSpriteAlpha(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency, Uint8 alpha);

    SDL_Point getTopLeftPosition(SDL_Point position, int size);
    SDL_Point computeCenterPosition(SDL_Point top_left_position, int size);
    SDL_Point computeTilePosition(SDL_Point top_left_position, int size);
    SDL_Point getCoordCenterTile(SDL_Point tile_position);

    // DEBUG
    void drawTileOutline(SDL_Point tile_position);
    void drawAllTileOutlines();
    // void drawColoredTile(SDL_Point tile_position);
    void drawAllColoredTiles();

private:
    GameModel& gameModel;

    // SDL window and surfaces
    SDL_Window* pWindow = nullptr;
    SDL_Surface* win_surf = nullptr;
    SDL_Surface* spriteSheet_NES = nullptr;
    SDL_Surface* spriteSheet_Namco_before_conversion = nullptr;
    SDL_Surface* spriteSheet_Namco = nullptr;
    // SDL_Renderer* renderer; // DEBUG

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
    static constexpr SDL_Rect num_sprites[10] = {
        { 3,53, TILE_SIZE,TILE_SIZE },  // 0
        { 12,53, TILE_SIZE,TILE_SIZE }, // 1
        { 19,53, TILE_SIZE,TILE_SIZE }, // 2
        { 27,53, TILE_SIZE,TILE_SIZE }, // 3
        { 35,53, TILE_SIZE,TILE_SIZE }, // 4
        { 43,53, TILE_SIZE,TILE_SIZE }, // 5
        { 51,53, TILE_SIZE,TILE_SIZE }, // 6
        { 59,53, TILE_SIZE,TILE_SIZE }, // 7
        { 67,53, TILE_SIZE,TILE_SIZE }, // 8
        { 75,53, TILE_SIZE,TILE_SIZE }  // 9
    };


    static constexpr SDL_Rect U_sprite = { 44,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect P_sprite = { 4,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect H_sprite = { 67,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect I_sprite = { 76,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect G_sprite = { 59,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect S_sprite = { 27,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect C_sprite = { 27,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect O_sprite = { 123,61, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect R_sprite = { 19,69, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect E_sprite = { 43,61, TILE_SIZE,TILE_SIZE };

    // Ghost sprites
    static constexpr int SIZE_GHOST_SPRITE = 14;
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
    // Directional sprites
    static constexpr SDL_Rect pacman_sprite_r = { 473,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_l = { 473,17, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_d = { 473,49, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_u = { 473,33, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    static constexpr SDL_Rect pacman_sprite_full = { 489,1, SIZE_PACMAN_SPRITE,SIZE_PACMAN_SPRITE  };
    // Death sprites
    static constexpr SDL_Rect pacman_death_sprites[11] = {
        { 503,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 520,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 536,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 552,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 568,3, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 584,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 600,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 616,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 632,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 648,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE },
        { 664,5, SIZE_PACMAN_SPRITE+3,SIZE_PACMAN_SPRITE }
    };
};
