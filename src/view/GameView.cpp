#include "GameView.h"
#include "model/GameModel.h"
#include "model/Character.h"
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

    render(gameModel.getGhost());
    render(gameModel.getPacMan());

	SDL_UpdateWindowSurface(pWindow);
}

void GameView::render(const Ghost& ghost) {
    // petit truc pour faire tourner le fantome
    SDL_Rect ghost_sprite_in;
    CharacterState state = ghost.getState();
    switch (state.direction) {
        case CharacterDirection::RIGHT:
            ghost_sprite_in = ghost.getSpriteR();
            break;
        case CharacterDirection::DOWN:
            ghost_sprite_in = ghost.getSpriteD();
            break;
        case CharacterDirection::LEFT:
            ghost_sprite_in = ghost.getSpriteL();
            break;
        case CharacterDirection::UP:
            ghost_sprite_in = ghost.getSpriteU();
            break;
    }

    // Update the position of the ghost sprite based on the CharacterState
    SDL_Rect ghost_sprite({ state.position.x,state.position.y, 32,32 }); // ici scale x2

    // ici on change entre les 2 sprites sources pour une jolie animation.
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite_in.x += 17;
    }

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, &ghost_sprite_in, win_surf, &ghost_sprite);
}

void GameView::render(const PacMan& pacman) {
    // petit truc pour faire tourner le fantome
    SDL_Rect pacman_sprite_in;
    CharacterState state = pacman.getState();
    switch (state.direction) {
        case CharacterDirection::RIGHT:
            pacman_sprite_in = pacman.getSpriteR();
            break;
        case CharacterDirection::DOWN:
            pacman_sprite_in = pacman.getSpriteD();
            break;
        case CharacterDirection::LEFT:
            pacman_sprite_in = pacman.getSpriteL();
            break;
        case CharacterDirection::UP:
            pacman_sprite_in = pacman.getSpriteU();
            break;
        case CharacterDirection::NONE:
            // TODO: set sprite to round sprite
            pacman_sprite_in = pacman.getSpriteR();
            break;
    }

    // Update the position of the ghost sprite based on the CharacterState
    SDL_Rect pacman_sprite({ state.position.x,state.position.y, 32,32 }); // ici scale x2

    // // ici on change entre les 2 sprites sources pour une jolie animation.
    // if ((gameModel.getCount() / 4) % 2) {
    //     pacman_sprite_in.x += 17;
    // }

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, &pacman_sprite_in, win_surf, &pacman_sprite);
}
