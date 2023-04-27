#include "GameView.h"
#include "model/GameModel.h"
#include "model/Character.h"
#include "model/Ghost.h"

#include <SDL.h>
#include <iostream>

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Point map_top_left={0,48};

SDL_Rect src_bg = { 200,3, 168,216 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect zero_sprite = { 3,52, 8,8 }; 
SDL_Rect one_sprite = { 12,52, 7,8 };
SDL_Rect U_sprite = { 43,68, 9,8 };  
SDL_Rect P_sprite = { 3,68, 8,8 }; 

SDL_Rect bg = { 0,48, MAP_WIDTH,MAP_HEIGHT }; 
SDL_Rect first_score_number_pos = { 80,16, 15,15};
SDL_Rect second_score_number_pos = { 96,16, 15,15};
SDL_Rect one_up_one_pos = { 48,0, 15,15};
SDL_Rect one_up_U_pos = { 64,0, 15,15};
SDL_Rect one_up_P_pos = { 80,0, 15,15};




GameView::GameView(GameModel& gameModel) : gameModel(gameModel) {
    // Initialize game view related data here
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH , WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    if (!plancheSprites) {
        // Handle error loading bitmap
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
}

GameView::~GameView() {
    // Clean up game view related data here
    SDL_FreeSurface(plancheSprites);
    SDL_DestroyWindow(pWindow);
}

void GameView::draw() {
    // Move the draw() function contents here
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);
    SDL_BlitScaled(plancheSprites, &zero_sprite, win_surf, &first_score_number_pos);
    SDL_BlitScaled(plancheSprites, &zero_sprite, win_surf, &second_score_number_pos);
    SDL_BlitScaled(plancheSprites, &one_sprite, win_surf, &one_up_one_pos);
    SDL_BlitScaled(plancheSprites, &U_sprite, win_surf, &one_up_U_pos);
    SDL_BlitScaled(plancheSprites, &P_sprite, win_surf, &one_up_P_pos);

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
