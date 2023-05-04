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
    void drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, Tile tile, bool transparency);
    void drawCharacterSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, Position position, bool transparency);
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

    // Other constants
    static constexpr int MAX_SCORE_DIGITS = 7;
};
