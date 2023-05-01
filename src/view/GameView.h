#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"
#include "common/GameDimensions.h"

#include <SDL.h>
#include <map>


class GameView {
public:
    GameView(GameModel& gameModel);
    ~GameView();

    void draw();
    void drawDeathAnimation(int death_sprite_count);

    void drawGhosts();
    void drawPacMan();

    void drawHUD();
    void drawMaze();
    void drawDots();

    void drawScoreHelper(int score, bool highscore);
    void drawScore();
    void drawHighScore();
    void drawText();
    void drawLives();

    void drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency);
    // DEBUG
    // void drawSpriteAlpha(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency, Uint8 alpha);

    // DEBUG
    void drawTileOutline(Tile tile);
    void drawAllTileOutlines();
    void drawAllColoredTiles();
    void drawPacmanPosition();

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

    // Window dimensions
    static constexpr int UPSCALED_WINDOW_WIDTH  = UPSCALING_FACTOR*WINDOW_WIDTH,
                         UPSCALED_WINDOW_HEIGHT = UPSCALING_FACTOR*WINDOW_HEIGHT;

    // Map sprites
    static constexpr SDL_Rect maze_Namco = { 28*TILE_SIZE+TILE_SIZE/2,0, MAZE_COLS*TILE_SIZE,MAZE_ROWS*TILE_SIZE }; // x,y, w,h (0,0) en haut a gauche
    static constexpr SDL_Rect maze_NES = { 200,3, 168,216 };

    // Other constants
    static constexpr int MAX_SCORE_DIGITS = 7;

    // HUP sprites
    static constexpr SDL_Rect life_sprite = { 584,16, SPRITE_SIZE,SPRITE_SIZE};
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

    // Coordinates of the top left corner of the character sprite grid
    // in the Namco sprite sheet
    static constexpr int GRID_ORIGIN = 456;

    // Ghost sprites
    std::map<Ghost::Type, std::map<Direction, SDL_Rect>> ghost_sprites = {
        {Ghost::Type::BLINKY, {
            {Direction::RIGHT, { GRID_ORIGIN              ,4*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::LEFT,  { GRID_ORIGIN+2*SPRITE_SIZE,4*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::UP,    { GRID_ORIGIN+4*SPRITE_SIZE,4*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::DOWN,  { GRID_ORIGIN+6*SPRITE_SIZE,4*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }}
        }},
        {Ghost::Type::PINKY,  {
            {Direction::RIGHT, { GRID_ORIGIN              ,5*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::LEFT,  { GRID_ORIGIN+2*SPRITE_SIZE,5*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::UP,    { GRID_ORIGIN+4*SPRITE_SIZE,5*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::DOWN,  { GRID_ORIGIN+6*SPRITE_SIZE,5*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }}
        }},
        {Ghost::Type::INKY,   {
            {Direction::RIGHT, { GRID_ORIGIN              ,6*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::LEFT,  { GRID_ORIGIN+2*SPRITE_SIZE,6*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::UP,    { GRID_ORIGIN+4*SPRITE_SIZE,6*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::DOWN,  { GRID_ORIGIN+6*SPRITE_SIZE,6*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }}
        }},
        {Ghost::Type::CLYDE,  {
            {Direction::RIGHT, { GRID_ORIGIN              ,7*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::LEFT,  { GRID_ORIGIN+2*SPRITE_SIZE,7*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::UP,    { GRID_ORIGIN+4*SPRITE_SIZE,7*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }},
            {Direction::DOWN,  { GRID_ORIGIN+6*SPRITE_SIZE,7*SPRITE_SIZE , SPRITE_SIZE,SPRITE_SIZE }}
        }}
    };

    // PacMan sprites
    // Directional sprites
    static constexpr SDL_Rect pacman_sprite_full = { GRID_ORIGIN+2*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE };

    static constexpr SDL_Rect pacman_sprites_r[4] = {
        { GRID_ORIGIN+2*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE }, // Full
        { GRID_ORIGIN+SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE }, // Slighly open
        { GRID_ORIGIN,0, SPRITE_SIZE,SPRITE_SIZE }, // Wide open
        { GRID_ORIGIN+SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE } // Slighly open
    };
    static constexpr SDL_Rect pacman_sprites_l[4] = {
        { GRID_ORIGIN+2*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE }, // Full
        { GRID_ORIGIN+SPRITE_SIZE,SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE }, // Slightly open
        { GRID_ORIGIN,SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE }, // Wide open
        { GRID_ORIGIN+SPRITE_SIZE,SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE } // Slightly open
    };
    static constexpr SDL_Rect pacman_sprites_u[4] = {
        { GRID_ORIGIN+2*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE }, // Full
        { GRID_ORIGIN+SPRITE_SIZE,2*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE }, // Slightly open
        { GRID_ORIGIN,2*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE }, // Wide open
        { GRID_ORIGIN+SPRITE_SIZE,2*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE } // Slightly open
    };
    static constexpr SDL_Rect pacman_sprites_d[4] = {
        { GRID_ORIGIN+2*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE }, // Full
        { GRID_ORIGIN+SPRITE_SIZE,3*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE }, // Slightly open
        { GRID_ORIGIN,3*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE }, // Wide open
        { GRID_ORIGIN+SPRITE_SIZE,3*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE } // Slightly open
    };
    // Death sprites
    static constexpr SDL_Rect pacman_death_sprites[11] = {
        { GRID_ORIGIN+3*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+4*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+5*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+6*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+7*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+8*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+9*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+10*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+11*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+12*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE },
        { GRID_ORIGIN+13*SPRITE_SIZE,0, SPRITE_SIZE,SPRITE_SIZE }
    };

    static constexpr SDL_Rect dot_sprite = { TILE_SIZE,TILE_SIZE, TILE_SIZE,TILE_SIZE };
    static constexpr SDL_Rect power_pellet_sprite = { TILE_SIZE,3*TILE_SIZE, TILE_SIZE,TILE_SIZE };
};
