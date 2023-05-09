#pragma once

#include "common/GameDimensions.h"

#include <map>

// Map sprites
static constexpr SDL_Rect maze_Namco = { 28*TILE_SIZE+TILE_SIZE/2,0, MAZE_COLS*TILE_SIZE,MAZE_ROWS*TILE_SIZE }; // x,y, w,h (0,0) en haut a gauche
static constexpr SDL_Rect maze_NES = { 200,3, 168,216 };

// HUP sprites
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
static constexpr SDL_Rect T_sprite = { 35,69, TILE_SIZE,TILE_SIZE};
static constexpr SDL_Rect A_sprite = { 12,61, TILE_SIZE,TILE_SIZE };

// Coordinates of the top left corner of the character sprite grid
// in the Namco sprite sheet
static constexpr int GRID_ORIGIN = 456;

// Life sprite
static constexpr SDL_Rect life_sprite = { GRID_ORIGIN+8*SPRITE_SIZE,SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE};

// Fruits sprites
// Cherry
static constexpr SDL_Rect cherry_sprite = { GRID_ORIGIN+2*SPRITE_SIZE,3*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE };

// Ready sprite
static constexpr SDL_Rect ready_sprite = { 0,0, 3*SPRITE_SIZE,SPRITE_SIZE};

// Game over sprite
static constexpr SDL_Rect game_over_sprite = { 0,0, 5*SPRITE_SIZE,SPRITE_SIZE};

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

// Ghost sprites Frightened
static constexpr SDL_Rect ghost_sprite_frightened_blue = { GRID_ORIGIN+8*SPRITE_SIZE,4*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE };
static constexpr SDL_Rect ghost_sprite_frightened_white= { GRID_ORIGIN+10*SPRITE_SIZE,4*SPRITE_SIZE, SPRITE_SIZE,SPRITE_SIZE };

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