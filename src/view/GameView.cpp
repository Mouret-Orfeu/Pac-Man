#include "GameView.h"
#include "Sprites.h"
#include "model/GameModel.h"
#include "model/Character.h"
#include "model/Ghost.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"

#include <SDL.h>
#include <iostream>


GameView::GameView(GameModel& game_model) : game_model(game_model) {
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
    drawBlackBackground();
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

    Position position = game_model.getPacMan().getPosition();

    drawCharacterSprite(spriteSheet_Namco, &pacman_death_sprites[death_sprite_num], position, true);

    SDL_UpdateWindowSurface(pWindow);
}

void GameView::drawBlackBackground() {
    SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 0, 0, 0));
}

void GameView::drawPacMan() {
    const PacMan& pacman = game_model.getPacMan();

    // ici on change entre les 2 sprites sources pour une jolie animation.
    int sprite_num = (pacman.getNbAnimatedFramesSinceLastSpeedChange() / 4) % 4;

    SDL_Rect pacman_sprite_in;
    Direction sprite_orientation = pacman.getDirection();
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

    drawCharacterSprite(spriteSheet_Namco, &pacman_sprite_in, pacman.getPosition(), true);

    // DEBUG
    //drawTileOutline(pacman.getPosition().toTile());
    //drawPacmanPosition();

    //DEBUG
    //Show teleportation tiles
    //drawTileOutline();
    //drawTileOutline({17, 27});

    //draw scatter_target_tile blinky pinky inky & clyde
    //drawTileOutline(game_model.getGhosts()[0]->getScatterTargetTile());
    //drawTileOutline(game_model.getGhosts()[1]->getScatterTargetTile());
    //drawTileOutline(game_model.getGhosts()[2]->getScatterTargetTile());
    //drawTileOutline(game_model.getGhosts()[3]->getScatterTargetTile());
}

void GameView::drawGhosts() {
    for (std::unique_ptr<Ghost>& ghost: game_model.getGhosts()) {
        Ghost::Type ghost_type = ghost->getType();
        Direction sprite_orientation = ghost->getDirection();
        SDL_Rect ghost_sprite;

        if (sprite_orientation != Direction::NONE) {
            if(ghost->getMode()==Ghost::Mode::FRIGHTENED)
                ghost_sprite= ghost_sprite_frightened_blue;
            else
                ghost_sprite = ghost_sprites[ghost_type][sprite_orientation];
            // Here we change between the 2 source sprites for a nice animation.
            if ((ghost->getNbAnimatedFramesSinceLastSpeedChange() / 16) % 2) {
                // The second sprite is just next to the first one
                ghost_sprite.x += SPRITE_SIZE;
                if (ghost->getMode()==Ghost::Mode::FRIGHTENED && game_model.getFrightenedCounter()>5*60) {
                    // The white sprites are two sprites next to the blue ones
                    ghost_sprite.x += 2*SPRITE_SIZE;
                }
            }
            drawCharacterSprite(spriteSheet_Namco, &ghost_sprite, ghost->getPosition(), true);

            //DEBUG
            if(ghost->getType() == Ghost::Type::PINKY)
                drawTileOutline(ghost->getCurrentTargetTile(), pink);
            if(ghost->getType() == Ghost::Type::BLINKY)
                drawTileOutline(ghost->getCurrentTargetTile(), red);
            if(ghost->getType() == Ghost::Type::INKY)
                drawTileOutline(ghost->getCurrentTargetTile(), blue);
            if(ghost->getType() == Ghost::Type::CLYDE)
                drawTileOutline(ghost->getCurrentTargetTile(), orange);
        }
    }
}

void GameView::drawMaze() {
    drawSprite(spriteSheet_Namco, &maze_Namco, Tile({3,0}), false);
}

void GameView::drawDots() {
    for (int i = 0; i < WINDOW_ROWS; i++) {
        for (int j = 0; j < WINDOW_COLS; j++) {
            Tile tile = {i, j};
            switch (game_model.getTile(tile))
            {
            case GameModel::TileType::DOT:
                drawSprite(spriteSheet_Namco, &dot_sprite, tile, true);
                break;
            case GameModel::TileType::ENERGIZER:
                if ((game_model.getFrameCount() / 16) % 2)
                    drawSprite(spriteSheet_Namco, &power_pellet_sprite, tile, true);
                break;
            default:
                break;
            }
        }
    }
}

void GameView::drawCharacterSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, Position position, bool transparency) {
    drawSprite(sprite_sheet, sprite, position.toTopLeft(), transparency);
}

void GameView::drawSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, Tile tile, bool transparency) {
    drawSprite(sprite_sheet, sprite, SDL_Point({tile.j*TILE_SIZE, tile.i*TILE_SIZE}), transparency);
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
// DEBUG
void GameView::drawPacmanPosition() {
    // Get Pac-Man's center position
    SDL_Point pacmanCenter = game_model.getPacMan().getPosition().toCenter();

    // Create a new surface with a green pixel
    SDL_Surface* greenPixel = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(greenPixel, NULL, SDL_MapRGB(greenPixel->format, 0, 255, 0));

    // Draw a green cross centered on Pac-Man's position
    int crossSize = 5; // You can adjust the size of the cross if necessary
    for (int i = -crossSize; i <= crossSize; ++i) {
        drawSprite(greenPixel, NULL, SDL_Point({pacmanCenter.x + i, pacmanCenter.y}), true);
        drawSprite(greenPixel, NULL, SDL_Point({pacmanCenter.x, pacmanCenter.y + i}), true);
    }

    // Free the temporary surface
    SDL_FreeSurface(greenPixel);
}

void GameView::drawGhostPosition(std::unique_ptr<Ghost> ghost) {
    // Get the ghost's center position
    SDL_Point ghostCenter = ghost->getPosition().toCenter();

    // Create a new surface with a red pixel
    SDL_Surface* redPixel = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(redPixel, NULL, SDL_MapRGB(redPixel->format, 255, 0, 0));

    // Draw a red cross centered on the ghost's position
    int crossSize = 5; // You can adjust the size of the cross if necessary
    for (int i = -crossSize; i <= crossSize; ++i) {
        drawSprite(redPixel, NULL, SDL_Point({ghostCenter.x + i, ghostCenter.y}), true);
        drawSprite(redPixel, NULL, SDL_Point({ghostCenter.x, ghostCenter.y + i}), true);
    }

    // Free the temporary surface
    SDL_FreeSurface(redPixel);
}



//DEBUG
void GameView::drawTileOutline(Tile tile, const SDL_Color& color) {
    // Create a new surface with the square outline in the desired color
    SDL_Surface* coloredSquare = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(coloredSquare, NULL, SDL_MapRGB(coloredSquare->format, color.r, color.g, color.b));
    SDL_Rect blackSquare = { 1,1, 6,6 };
    SDL_FillRect(coloredSquare, &blackSquare, SDL_MapRGB(coloredSquare->format, 0, 0, 0));

    // Copy the square outline onto the main surface
    drawSprite(coloredSquare, NULL, tile, true);

    // Free the temporary surface
    SDL_FreeSurface(coloredSquare);
}

//DEBUG
void GameView::drawAllTileOutlines() {
    for(int i = 0; i < WINDOW_ROWS; i++)
        for (int j = 0; j < WINDOW_COLS; j++)
            drawTileOutline({i,j}, red);
}

// DEBUG
void GameView::drawAllColoredTiles() {
    for (int i = 0; i < WINDOW_ROWS; i++) {
        for (int j = 0; j < WINDOW_COLS; j++) {
            // Get the cell type
            GameModel::TileType cell = game_model.getTile({i, j});

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
            drawSprite(coloredTile, NULL, Tile({i,j}), true);

            // Free the temporary surface
            SDL_FreeSurface(coloredTile);
        }
    }
}



void GameView::drawHUD() {
    drawScore();
    drawHighScore();
    drawLives();
    drawFruit();
    drawText(); // "1UP" and "HIGH SCORE"
}

void GameView::drawScore() {
    int score = game_model.getPacMan().getScore();
    drawScoreHelper(score, false);
}

void GameView::drawHighScore() {
    int highscore = game_model.getPacMan().getHighScore();
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
            drawSprite(spriteSheet_NES, &num_sprites[num], Tile({1, initialPosition}), false);

        initialPosition--;
    }
}

void GameView::drawText() {
    // 1UP
    drawSprite(spriteSheet_NES, &num_sprites[1], Tile({0,3}), true);
    drawSprite(spriteSheet_NES, &U_sprite, Tile({0,4}), true);
    drawSprite(spriteSheet_NES, &P_sprite, Tile({0,5}), true);

    // HIGH SCORE
    drawSprite(spriteSheet_NES, &H_sprite, Tile({0,10}), true);
    drawSprite(spriteSheet_NES, &I_sprite, Tile({0,11}), true);
    drawSprite(spriteSheet_NES, &G_sprite, Tile({0,12}), true);
    drawSprite(spriteSheet_NES, &H_sprite, Tile({0,13}), true);

    drawSprite(spriteSheet_NES, &S_sprite, Tile({0,15}), true);
    drawSprite(spriteSheet_NES, &C_sprite, Tile({0,16}), true);
    drawSprite(spriteSheet_NES, &O_sprite, Tile({0,17}), true);
    drawSprite(spriteSheet_NES, &R_sprite, Tile({0,18}), true);
    drawSprite(spriteSheet_NES, &E_sprite, Tile({0,19}), true);
}

void GameView::drawLives() {
    int lives = game_model.getPacMan().getLives();

    //DEBUG
    //std::cout << "Lives: " << lives << std::endl;


    // Clear the area where the lives are drawn
    SDL_Surface* cleared_life_surf = SDL_CreateRGBSurface(0, SPRITE_SIZE, SPRITE_SIZE, 32, 0, 0, 0, 0);
    for(int i=1; i<=3; i++ )
        drawSprite(cleared_life_surf, NULL, Tile({WINDOW_ROWS-2,2*i}), false);

    // Draw lives
    for (int i = 1; i <= lives; i++)
        drawSprite(spriteSheet_Namco, &life_sprite, Tile({WINDOW_ROWS-2,2*i}), true);
}

void GameView::drawFruit() {
    //bool fruit = game_model.getPacMan().getFruit();

    //DEBUG
    //std::cout << "Lives: " << lives << std::endl;



    // Draw fruit
    drawSprite(spriteSheet_Namco, &cherry_sprite, Tile({WINDOW_ROWS-2,24}), true);
}
