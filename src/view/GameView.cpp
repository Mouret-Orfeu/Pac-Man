#include "GameView.h"
#include "Sprites.h"
#include "model/GameModel.h"
#include "model/Character.h"
#include "model/Ghost.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"

#include <SDL.h>
#include <iostream>


GameView::GameView(GameModel& gameModel) : gameModel(gameModel) {
    // Initialize game view related data here
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, UPSCALED_WINDOW_WIDTH , UPSCALED_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

    //On utilise des sprites venant des ces 2 fichiers
	spriteSheet_NES = SDL_LoadBMP("./assets/pacman_sprites_NES.bmp");
    spriteSheet_Namco_before_conversion = SDL_LoadBMP("./assets/pacman_sprites_Namco.bmp");

    if ((!spriteSheet_NES) || (!spriteSheet_Namco_before_conversion)) {
        // Handle error loading bitmap
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    spriteSheet_Namco = SDL_ConvertSurface(spriteSheet_Namco_before_conversion, win_surf->format, 0);

    // if (SDL_SaveBMP(spriteSheet_Namco, "pacman_sprites_Namco_formatted.bmp") != 0) {
    //     // handle error
    //     std::cerr << "Failed to save bitmap: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     exit(1);
    // }

    if(!spriteSheet_Namco) {
        // Handle error converting bitmap
        std::cerr << "Failed to convert bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    //DEBUG
    //grid_surface = SDL_CreateRGBSurface(0, UPSCALED_WINDOW_WIDTH, UPSCALED_WINDOW_HEIGHT, 32, 0, 0, 0, 0);
    //SDL_FillRect(grid_surface, NULL, SDL_MapRGB(grid_surface->format, 255, 0, 0)); // fill grid surface with red color

    // DEBUG
    // Create the renderer for the window
    // renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (renderer == NULL) {
    //     printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    // }
}

GameView::~GameView() {
    // Clean up game view related data here
    SDL_FreeSurface(spriteSheet_NES);
    SDL_FreeSurface(spriteSheet_Namco_before_conversion);
    SDL_FreeSurface(spriteSheet_Namco);
    // SDL_DestroyRenderer(renderer); // DEBUG
    SDL_DestroyWindow(pWindow);
}

void GameView::draw() {
    drawMaze();
    drawDots();
    drawHUD();

    // Draw Characters
    // PacMan
    drawPacMan();
    // Ghosts
    drawGhosts();

    // drawAllTileOutlines();
    // drawAllColoredTiles();

	SDL_UpdateWindowSurface(pWindow);
}

void GameView::drawDeathAnimation(int death_sprite_num) {
    drawMaze();
    drawHUD();

    SDL_Point position = gameModel.getPacMan().getPosition().toTopLeft();

    drawSprite(spriteSheet_Namco, &pacman_death_sprites[death_sprite_num], position, true);

    SDL_UpdateWindowSurface(pWindow);
}

void GameView::drawPacMan() {
    const PacMan& pacman = gameModel.getPacMan();

    // ici on change entre les 2 sprites sources pour une jolie animation.
    int sprite_num = (gameModel.getCount() / 4) % 4;

    SDL_Rect pacman_sprite_in;
    Direction sprite_orientation = pacman.getSpriteOrientation();
    switch (sprite_orientation) {
        case Direction::RIGHT:
            pacman_sprite_in = pacman_sprites_r[sprite_num];
            break;
        case Direction::DOWN:
            pacman_sprite_in = pacman_sprites_d[sprite_num];
            break;
        case Direction::LEFT:
            pacman_sprite_in = pacman_sprites_l[sprite_num];
            break;
        case Direction::UP:
            pacman_sprite_in = pacman_sprites_u[sprite_num];
            break;
        case Direction::NONE:
            // TODO: set sprite to round sprite
            pacman_sprite_in = pacman_sprite_full;
            break;
    }

    drawSprite(spriteSheet_Namco, &pacman_sprite_in, pacman.getPosition().toTopLeft(), true);

    // DEBUG
    drawTileOutline(pacman.getPosition().toTile());
    drawPacmanPosition();

    //DEBUG
    //Show teleportation tiles
    //drawTileOutline();
    //drawTileOutline({17, 27});

    //draw scatter_target_tile blinky pinky inky & clyde
    //drawTileOutline(gameModel.getGhosts()[0]->getScatterTargetTile());
    //drawTileOutline(gameModel.getGhosts()[1]->getScatterTargetTile());
    //drawTileOutline(gameModel.getGhosts()[2]->getScatterTargetTile());
    //drawTileOutline(gameModel.getGhosts()[3]->getScatterTargetTile());


}

void GameView::drawGhosts() {
    for (std::unique_ptr<Ghost>& ghost: gameModel.getGhosts()) {
        Ghost::Type ghost_type = ghost->getType();
        Direction sprite_orientation = ghost->getSpriteOrientation();

        if (sprite_orientation != Direction::NONE) {
            SDL_Rect ghost_sprite = ghost_sprites[ghost_type][sprite_orientation];
            // Here we change between the 2 source sprites for a nice animation.
            if ((gameModel.getCount() / 8) % 2) {
                // The second sprite is just next to the first one
                ghost_sprite.x += SPRITE_SIZE;
            }
            drawSprite(spriteSheet_Namco, &ghost_sprite, ghost->getPosition().toTopLeft(), true);
        }

    }

}

void GameView::drawMaze() {
    drawSprite(spriteSheet_Namco, &maze_Namco, {0,3*TILE_SIZE}, false);
}

// class GameModel {
// public:
//     // Maze cells
//     enum class TileType {
//         WALL = -1,
//         EMPTY = 0,
//         DOT = 1,
//         ENERGIZER = 2,
//         // FRUIT = 3,
//     };

//     TileType tilesMatrix[WINDOW_ROWS][WINDOW_COLS];
// }

void GameView::drawDots() {
    for (int i = 0; i < WINDOW_ROWS; i++) {
        for (int j = 0; j < WINDOW_COLS; j++) {
            switch (gameModel.getTile({i, j}))
            {
            case GameModel::TileType::DOT:
                drawSprite(spriteSheet_Namco, &dot_sprite, {j*TILE_SIZE, i*TILE_SIZE}, true);
                break;
            case GameModel::TileType::ENERGIZER:
                drawSprite(spriteSheet_Namco, &power_pellet_sprite, {j*TILE_SIZE, i*TILE_SIZE}, true);
                break;
            default:
                break;
            }
        }
    }
}

void GameView::drawHUD() {
    drawScore();
    drawHighScore();
    drawLives();
    drawText(); // "1UP" and "HIGH SCORE"
}

void GameView::drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency) {
    // Set the black pixels transparency
    SDL_SetColorKey(sprite_sheet, transparency, 0);

    // Get the sprite size
    int w, h;
    if (sprite != NULL) {
        w = sprite->w;
        h = sprite->h;
    } else {
        w = sprite_sheet->w;
        h = sprite_sheet->h;
    }

    // Create an upscaled sprite at the right position
    SDL_Rect sprite_out = { UPSCALING_FACTOR*top_left_position.x,UPSCALING_FACTOR*top_left_position.y, UPSCALING_FACTOR*w,UPSCALING_FACTOR*h };

    // Copy the upscaled sprite to the window surface
    if(SDL_BlitScaled(sprite_sheet, sprite, win_surf, &sprite_out)<0){
        printf("SDL_BlitScaled failed: %s\n", SDL_GetError());
    }
}

// // DEBUG
// void GameView::drawSpriteAlpha(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency, Uint8 alpha) {
//     // Set the black pixels transparency
//     // SDL_SetColorKey(sprite_sheet, transparency, 0);
//     SDL_SetColorKey(sprite_sheet, transparency ? SDL_TRUE : SDL_FALSE, 0);


//     // Get the sprite size
//     int w, h;
//     if (sprite != NULL) {
//         w = sprite->w;
//         h = sprite->h;
//     } else {
//         w = sprite_sheet->w;
//         h = sprite_sheet->h;
//     }

//     // Create an upscaled sprite at the right position
//     SDL_Rect sprite_out = { UPSCALING_FACTOR * top_left_position.x, UPSCALING_FACTOR * top_left_position.y, UPSCALING_FACTOR * w, UPSCALING_FACTOR * h };

//     // Create a texture from the sprite sheet
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sprite_sheet);

//     // Enable blending for the texture
//     if (transparency) {
//         SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//     }

//     // Set the alpha value for the texture
//     SDL_SetTextureAlphaMod(texture, alpha);

//     // Copy the texture to the renderer
//     if (SDL_RenderCopy(renderer, texture, sprite, &sprite_out) < 0) {
//         printf("SDL_RenderCopy failed: %s\n", SDL_GetError());
//     }

//     // Destroy the texture
//     SDL_DestroyTexture(texture);
// }

// DEBUG
void GameView::drawPacmanPosition() {
    // Get Pac-Man's center position
    SDL_Point pacmanCenter = gameModel.getPacMan().getPosition().toCenter();

    // Create a new surface with a green pixel
    SDL_Surface* greenPixel = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(greenPixel, NULL, SDL_MapRGB(greenPixel->format, 0, 255, 0));

    // Draw a green cross centered on Pac-Man's position
    int crossSize = 5; // You can adjust the size of the cross if necessary
    for (int i = -crossSize; i <= crossSize; ++i) {
        drawSprite(greenPixel, NULL, {pacmanCenter.x + i, pacmanCenter.y}, true);
        drawSprite(greenPixel, NULL, {pacmanCenter.x, pacmanCenter.y + i}, true);
    }

    // Free the temporary surface
    SDL_FreeSurface(greenPixel);
}

//DEBUG
void GameView::drawTileOutline(Tile tile) {
    int x = tile.j*TILE_SIZE,
        y = tile.i*TILE_SIZE;
    // Create a new surface with the square outline
    SDL_Surface* redSquare = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(redSquare, NULL, SDL_MapRGB(redSquare->format, 255, 0, 0));
    SDL_Rect blackSquare = { 1,1, 6,6 };
    SDL_FillRect(redSquare, &blackSquare, SDL_MapRGB(redSquare->format, 0, 0, 0));

    // Copy the square outline onto the main surface
    drawSprite(redSquare, NULL, {x,y}, true);

    // Free the temporary surface
    SDL_FreeSurface(redSquare);
}

//DEBUG
void GameView::drawAllTileOutlines() {
    for(int i = 0; i < WINDOW_ROWS; i++)
        for (int j = 0; j < WINDOW_COLS; j++)
            drawTileOutline({i,j});
}

// DEBUG
void GameView::drawAllColoredTiles() {
    for (int i = 0; i < WINDOW_ROWS; i++) {
        for (int j = 0; j < WINDOW_COLS; j++) {
            // Get the cell type
            GameModel::TileType cell = gameModel.getTile({i, j});

            // Define colors for different cell types
            SDL_Color color;
            Uint8 alpha = 255; // Semi-transparent

            switch (cell) {
                case GameModel::TileType::WALL:
                    color = {255, 0, 0, alpha}; // Red
                    break;
                case GameModel::TileType::EMPTY:
                    color = {0, 255, 0, alpha}; // Green
                    break;
                case GameModel::TileType::DOT:
                    color = {0, 0, 255, alpha}; // Blue
                    break;
                case GameModel::TileType::ENERGIZER:
                    color = {255, 255, 0, alpha}; // Yellow
                    break;
                default:
                    continue; // Skip if unknown cell type
            }

            // Create a new surface with the tile color
            SDL_Surface* coloredTile = SDL_CreateRGBSurface(0, TILE_SIZE, TILE_SIZE, 32, 0, 0, 0, 0);
            SDL_FillRect(coloredTile, NULL, SDL_MapRGBA(coloredTile->format, color.r, color.g, color.b, color.a));

            // Copy the colored tile onto the main surface
            SDL_Point dst = {j * TILE_SIZE, i * TILE_SIZE};
            drawSprite(coloredTile, NULL, dst, true);

            // Free the temporary surface
            SDL_FreeSurface(coloredTile);
        }
    }
}

void GameView::drawScore() {
    int score = gameModel.getPacMan().getScore();
    drawScoreHelper(score, false);
}

void GameView::drawHighScore() {
    int highscore = gameModel.getPacMan().getHighScore();
    drawScoreHelper(highscore, true);
}

void GameView::drawScoreHelper(int score, bool highscore) {
    // Convert the score to a string
    std::string scoreString = std::to_string(score);

    // If the score is 0 and not a highscore, display 00
    if (score == 0) {
        if (highscore) {
            // If the highscore is 0, do not display anything
            return;
        } else {
            // If the score is 0, display 00
            scoreString = "00";
        }
    }

    // Determine the initial position based on whether it's a highscore or not
    int initialPosition = MAX_SCORE_DIGITS-1;
    if (highscore)
        initialPosition+=11;

    // Loop through the characters in the score string, starting from the rightmost digit
    for (int i = scoreString.length() - 1; i >= 0; i--)
    {
        // Get the current digit
        int num = scoreString[i] - '0';

        // Draw the digit if valid
        if (0 <= num && num <= 9)
            drawSprite(spriteSheet_NES, &num_sprites[num], SDL_Point({initialPosition*TILE_SIZE,1*TILE_SIZE}), false);

        initialPosition--;
    }
}

void GameView::drawText() {
    // 1UP
    drawSprite(spriteSheet_NES, &num_sprites[1], SDL_Point({3*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &U_sprite, SDL_Point({4*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &P_sprite, SDL_Point({5*TILE_SIZE, 0}), true);

    // HIGH SCORE
    drawSprite(spriteSheet_NES, &H_sprite, SDL_Point({10*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &I_sprite, SDL_Point({11*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &G_sprite, SDL_Point({12*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &H_sprite, SDL_Point({13*TILE_SIZE, 0}), true);

    drawSprite(spriteSheet_NES, &S_sprite, SDL_Point({15*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &C_sprite, SDL_Point({16*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &O_sprite, SDL_Point({17*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &R_sprite, SDL_Point({18*TILE_SIZE, 0}), true);
    drawSprite(spriteSheet_NES, &E_sprite, SDL_Point({19*TILE_SIZE, 0}), true);
}

void GameView::drawLives() {
    int lives = gameModel.getPacMan().getLives();
    for (int i = 1; i <= lives; i++)
        drawSprite(spriteSheet_Namco, &life_sprite, SDL_Point({2*i*TILE_SIZE+3,WINDOW_HEIGHT-2*TILE_SIZE+2}), true);
}
