#include "GameView.h"
#include "model/GameModel.h"
#include "model/Character.h"
#include "model/Ghost.h"

#include <SDL.h>
#include <iostream>


GameView::GameView(GameModel& gameModel) : gameModel(gameModel) {
    // Initialize game view related data here
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH , WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

    //On utilise des sprites venant des ces 2 fichiers
	spriteSheet_NES = SDL_LoadBMP("./assets/pacman_sprites_NES.bmp");
    spriteSheet_Namco = SDL_LoadBMP("./assets/pacman_sprites_Namco.bmp");

    if ((!spriteSheet_NES) || (!spriteSheet_Namco)) {
        // Handle error loading bitmap
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    spriteSheet_Namco_formatted = SDL_ConvertSurface(spriteSheet_Namco, win_surf->format, 0);

    // if (SDL_SaveBMP(spriteSheet_Namco_formatted, "pacman_sprites_Namco_formatted.bmp") != 0) {
    //     // handle error
    //     std::cerr << "Failed to save bitmap: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     exit(1);
    // }

    if(!spriteSheet_Namco_formatted) {
        // Handle error converting bitmap
        std::cerr << "Failed to convert bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    //DEBUG
    //grid_surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
    //SDL_FillRect(grid_surface, NULL, SDL_MapRGB(grid_surface->format, 255, 0, 0)); // fill grid surface with red color
}

GameView::~GameView() {
    // Clean up game view related data here
    SDL_FreeSurface(spriteSheet_NES);
    SDL_FreeSurface(spriteSheet_Namco);
    SDL_FreeSurface(spriteSheet_Namco_formatted);
    SDL_DestroyWindow(pWindow);
}

void GameView::draw() {
    renderMaze();
    renderHUD();
    render(gameModel.getGhost());
    render(gameModel.getPacMan());

	SDL_UpdateWindowSurface(pWindow);
}

void GameView::render(const Ghost& ghost) {
    // petit truc pour faire tourner le fantome
    SDL_Rect ghost_sprite;
    Ghost::State state = ghost.getState();
    switch (state.direction) {
        case Ghost::Direction::RIGHT:
            ghost_sprite = Blinky_sprite_r;
            break;
        case Ghost::Direction::DOWN:
            ghost_sprite = Blinky_sprite_d;
            break;
        case Ghost::Direction::LEFT:
            ghost_sprite = Blinky_sprite_l;
            break;
        case Ghost::Direction::UP:
            ghost_sprite = Blinky_sprite_u;
            break;
    }

    // ici on change entre les 2 sprites sources pour une jolie animation.
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite.x += 16;
    }

    renderSprite(spriteSheet_Namco_formatted, &ghost_sprite, getTopLeftPosition(state.center_position, SIZE_GHOST_SPRITE), true);
}

void GameView::render(const PacMan& pacman) {
    // petit truc pour faire tourner le fantome
    SDL_Rect pacman_sprite_in;
    PacMan::State state = pacman.getState();
    switch (state.direction) {
        case PacMan::Direction::RIGHT:
            pacman_sprite_in = pacman_sprite_r;
            break;
        case PacMan::Direction::DOWN:
            pacman_sprite_in = pacman_sprite_d;
            break;
        case PacMan::Direction::LEFT:
            pacman_sprite_in = pacman_sprite_l;
            break;
        case PacMan::Direction::UP:
            pacman_sprite_in = pacman_sprite_u;
            break;
        case PacMan::Direction::NONE:
            // TODO: set sprite to round sprite
            pacman_sprite_in = pacman_sprite_r;
            break;
    }

    // // ici on change entre les 2 sprites sources pour une jolie animation.
    // if ((gameModel.getCount() / 4) % 2) {
    //     pacman_sprite_in.x += 17;
    // }

    renderSprite(spriteSheet_Namco_formatted, &pacman_sprite_in, getTopLeftPosition(state.center_position, SIZE_PACMAN_SPRITE), true);

    TileOutline(win_surf, state.tile_position);
}

void GameView::renderMaze() {
    renderSprite(spriteSheet_Namco_formatted, &map_sprite_originale, {0,3*TILE_SIZE}, false);
}

void GameView::renderHUD() {
    // Score
    renderSprite(spriteSheet_NES, &zero_sprite, SDL_Point({5*TILE_SIZE,TILE_SIZE}), true);
    renderSprite(spriteSheet_NES, &zero_sprite, SDL_Point({6*TILE_SIZE,TILE_SIZE}), true);

    // 1UP
    renderSprite(spriteSheet_NES, &one_sprite, SDL_Point({3*TILE_SIZE,0}), true);
    renderSprite(spriteSheet_NES, &U_sprite, SDL_Point({4*TILE_SIZE,0}), true);
    renderSprite(spriteSheet_NES, &P_sprite, SDL_Point({5*TILE_SIZE,0}), true);

    // Lives
    renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({2*TILE_SIZE+3,HEIGHT-2*TILE_SIZE+2}), true);
    renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({4*TILE_SIZE+3,HEIGHT-2*TILE_SIZE+2}), true);
    renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({6*TILE_SIZE+3,HEIGHT-2*TILE_SIZE+2}), true);
}


void GameView::renderSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency) {
    // Set the black pixels transparency
    SDL_SetColorKey(sprite_sheet, transparency, 0);
    // Create an upscaled sprite at the right position
    int w, h;
    if (sprite != NULL) {
        w = sprite->w;
        h = sprite->h;
    } else {
        w = sprite_sheet->w;
        h = sprite_sheet->h;
    }
    SDL_Rect sprite_out = {UPSCALING_FACTOR*top_left_position.x, UPSCALING_FACTOR*top_left_position.y, UPSCALING_FACTOR*w, UPSCALING_FACTOR*h};
    // Copy the upscaled sprite to the window surface
    if(SDL_BlitScaled(sprite_sheet, sprite, win_surf, &sprite_out)<0){
        printf("SDL_BlitScaled failed: %s\n", SDL_GetError());
    }
}

SDL_Point GameView::computeCenterPosition(SDL_Point top_left_position, int size) {
    return {top_left_position.x+(size-1)/2, top_left_position.y+(size-1)/2};
}

SDL_Point GameView::computeTilePosition(SDL_Point top_left_position, int size) {
    SDL_Point center_position = computeCenterPosition(top_left_position, size);
    return {center_position.x/8, center_position.y/8};
}

SDL_Point GameView::getCoordCenterTile(SDL_Point tile_pos) {
    return {tile_pos.x*8+4, tile_pos.y*8+4};
}

SDL_Point GameView::getTopLeftPosition(SDL_Point position, int size) {
    return {position.x-(size-1)/2, position.y-(size-1)/2};
}

//DEBUG
void GameView::TileOutline(SDL_Surface* win_surf, SDL_Point tile_position) {
    int x = tile_position.x*TILE_SIZE,
        y = tile_position.y*TILE_SIZE;
    // Create a new surface with the square outline
    SDL_Surface* redSquare = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(redSquare, NULL, SDL_MapRGB(redSquare->format, 255, 0, 0));
    SDL_Rect blackSquare = { 1,1, 6,6 };
    SDL_FillRect(redSquare, &blackSquare, SDL_MapRGB(redSquare->format, 0, 0, 0));

    // Copy the square outline onto the main surface
    // SDL_Rect destRect = { x,y, 8,8 };
    SDL_SetColorKey(redSquare, true, 0);
    renderSprite(redSquare, NULL, {x,y}, true);
    // SDL_BlitSurface(redSquare, NULL, win_surf, &destRect);

    // Free the temporary surface
    SDL_FreeSurface(redSquare);
}

//DEBUG
void GameView::drawAllTileOutlines() {
    for(int i = 0; i < 28; i++)
        for (int j = 0; j < 36; j++)
            TileOutline(win_surf, {i,j});
}
