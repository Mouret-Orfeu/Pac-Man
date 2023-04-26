#include "GameView.h"
#include "model/GameModel.h"
#include "model/Ghost.h"

#include <SDL.h>
#include <iostream>

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect src_bg = { 200,3, 168,216 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { 4,4, 672,864 }; // ici scale x4

GameView::GameView(GameModel& gameModel) : gameModel(gameModel) {
    // Initialize game view related data here
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
}

GameView::~GameView() {
    // Clean up game view related data here
}

void GameView::draw() {
    // Move the draw() function contents here
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    renderGhost(gameModel.getGhost());

	SDL_UpdateWindowSurface(pWindow);
}

// Implement game view-related methods here
void GameView::renderGhost(const Ghost& ghost) {
    // petit truc pour faire tourner le fantome
    const SDL_Rect* ghost_sprite_in;
    GhostState state = ghost.getState();
    switch (state.direction) {
        case GhostDirection::RIGHT:
            ghost_sprite_in = &ghost.getSpriteR();
            break;
        case GhostDirection::DOWN:
            ghost_sprite_in = &ghost.getSpriteD();
            break;
        case GhostDirection::LEFT:
            ghost_sprite_in = &ghost.getSpriteL();
            break;
        case GhostDirection::UP:
            ghost_sprite_in = &ghost.getSpriteU();
            break;
    }

    // Update the position of the ghost sprite based on the GhostState
    SDL_Rect ghost_sprite({ state.position.x,state.position.y, 32,32 }); // ici scale x2

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_sprite_in2 = *ghost_sprite_in;
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite_in2.x += 17;
    }

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, &ghost_sprite_in2, win_surf, &ghost_sprite);
}
