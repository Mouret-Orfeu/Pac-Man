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
    static constexpr SDL_Point init_pos_tile_pacman = { init_pos_center_pacman.x/24, init_pos_center_pacman.y/24};

    

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
    void draw_death(int death_sprite_count);

    void render(const Ghost& ghost);
    void render(const PacMan& pacman);
    void renderHUD();
    void renderMaze();

    SDL_Surface* getPrintableScore(int score);
    void displayScore(int score);
    void displayText();
    void dilplayHighScore(int highScore);
    void displayLives(int lives);

    void displayPacmanDeath(int death_frame);
private:
    GameModel& gameModel;

    // SDL window and surfaces
    SDL_Window* pWindow = nullptr;
    SDL_Surface* win_surf = nullptr;
    SDL_Surface* spriteSheet_NES = nullptr;
    SDL_Surface* spriteSheet_Namco = nullptr;
    SDL_Surface* spriteSheet_Namco_formatted = nullptr;


   

    // Constants for the top left corner of the maze and various sprites
    static constexpr int MAX_SCORE_DIGITS = 7;
    static constexpr int SIZE_LIFE_SPRITE = 11;
    static constexpr int SIZE_LIFE_SPRITE_RESIZED = UPSCALING_FACTOR*SIZE_LIFE_SPRITE;

    static constexpr SDL_Point map_top_left = {0,3*TILE_SIZE};
    static constexpr SDL_Rect map_sprite_originale = { 0,0, MAZE_COLS*ORIGINAL_TILE_SIZE,MAZE_ROWS*ORIGINAL_TILE_SIZE }; // x,y, w,h (0,0) en haut a gauche
    static constexpr SDL_Rect map_sprite_prof = { 200,3, 168,216 };
    
    static constexpr SDL_Rect zero_sprite = { 3,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect one_sprite = { 12,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect two_sprite = { 19,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect three_sprite = { 27,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect four_sprite = { 35,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect five_sprite = { 43,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect six_sprite = { 51,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect seven_sprite = { 59,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect eight_sprite = { 67,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect nine_sprite = { 75,53, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };   


    static constexpr SDL_Rect U_sprite = { 44,69, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect P_sprite = { 4,69, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect H_sprite = { 67,61, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect I_sprite = { 76,61, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect G_sprite = { 59,61, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect C_sprite = { 27,61, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect O_sprite = { 123,61, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect E_sprite = { 43,61, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect R_sprite = { 19,69, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };
    static constexpr SDL_Rect S_sprite = { 27,69, ORIGINAL_TILE_SIZE,ORIGINAL_TILE_SIZE };


    static constexpr SDL_Rect life_sprite = { 587,18, SIZE_LIFE_SPRITE,SIZE_LIFE_SPRITE};


    
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


    // SDL rectangles for maze and HUP elements
    SDL_Rect bg = { 0,3*TILE_SIZE, MAZE_COLS*TILE_SIZE,MAZE_ROWS*TILE_SIZE };

    SDL_Rect first_score_number_pos = { 5*TILE_SIZE,TILE_SIZE, TILE_SIZE,TILE_SIZE };
    SDL_Rect second_score_number_pos = { 6*TILE_SIZE,TILE_SIZE, TILE_SIZE,TILE_SIZE };

    SDL_Rect one_up_one_pos = { 3*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect one_up_U_pos = { 4*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect one_up_P_pos = { 5*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };

    SDL_Rect H1_high_score_pos = { 10*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect I_high_score_pos = { 11*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect G_high_score_pos = { 12*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect H2_high_score_pos = { 13*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect S_high_score_pos = { 15*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect C_high_score_pos = { 16*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect O_high_score_pos = { 17*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect R_high_score_pos = { 18*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };
    SDL_Rect E_high_score_pos = { 19*TILE_SIZE,0, TILE_SIZE,TILE_SIZE };

    SDL_Rect first_life_pos = { 2*TILE_SIZE+UPSCALING_FACTOR*3,WINDOW_HEIGHT-2*TILE_SIZE+UPSCALING_FACTOR*2, SIZE_LIFE_SPRITE_RESIZED,SIZE_LIFE_SPRITE_RESIZED};
    SDL_Rect second_life_pos = { 4*TILE_SIZE+UPSCALING_FACTOR*3,WINDOW_HEIGHT-2*TILE_SIZE+UPSCALING_FACTOR*2, SIZE_LIFE_SPRITE_RESIZED,SIZE_LIFE_SPRITE_RESIZED };
    SDL_Rect third_life_pos = { 6*TILE_SIZE+UPSCALING_FACTOR*3,WINDOW_HEIGHT-2*TILE_SIZE+UPSCALING_FACTOR*2, SIZE_LIFE_SPRITE_RESIZED,SIZE_LIFE_SPRITE_RESIZED };

};
