#pragma once

#include "model/GameModel.h"
#include "model/Ghost.h"
#include "common/GameDimensions.h"

#include <SDL.h>


class GameView {
public:
    GameView(GameModel& game_model);
    ~GameView();

    void draw();
    void drawDeathAnimation(int death_sprite_count);

    void drawBlackBackground();
    void drawMaze();
    void drawDots();

    void drawGhosts();
    void drawPacMan();

    void drawHUD();
    void drawScoreHelper(int score, bool highscore);
    void drawScore();
    void drawHighScore();
    void drawText();
    void drawLives();
    void drawFruit();

    void drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency);
    void drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, Tile tile, bool transparency);
    void drawCharacterSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, Position position, bool transparency);


    void drawTileOutline(Tile tile, const SDL_Color& color);
    void drawAllTileOutlines();
    void drawAllColoredTiles();
    void drawPacmanPosition();
    void drawGhostPosition(std::unique_ptr<Ghost> ghost);

private:
    GameModel& game_model;

    // SDL window and surfaces
    SDL_Window* pWindow = nullptr;
    SDL_Surface win_surf;
    SDL_Surface* spriteSheet_NES = nullptr;
    SDL_Surface* spriteSheet_Namco_before_conversion = nullptr;
    SDL_Surface* spriteSheet_Namco = nullptr;
    SDL_Surface* readySheet = nullptr;
    SDL_Surface* gameOverSheet = nullptr;
    // SDL_Renderer* renderer; // DEBUG
    SDL_Color red = { 255, 0, 0 };
    SDL_Color orange = { 255, 165, 0 };
    SDL_Color pink = { 255, 105, 180 };
    SDL_Color blue = {173, 216, 230, 255};

    // Upscaling factor
    static constexpr int UPSCALING_FACTOR = 3;

    // Window dimensions
    static constexpr int UPSCALED_WINDOW_WIDTH  = UPSCALING_FACTOR*WINDOW_WIDTH,
                         UPSCALED_WINDOW_HEIGHT = UPSCALING_FACTOR*WINDOW_HEIGHT;

    // Other constants
    static constexpr int MAX_SCORE_DIGITS = 7;
};
