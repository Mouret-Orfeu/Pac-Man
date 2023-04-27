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
	plancheSprites_prof = SDL_LoadBMP("./assets/pacman_sprites.bmp");
    plancheSprites_originale = SDL_LoadBMP("./assets/pacman_sprites_original.bmp");

    plancheSprites_originale_formatted = SDL_ConvertSurface(plancheSprites_originale, win_surf->format, 0);

    if ((!plancheSprites_prof) || (!plancheSprites_originale)) {
        // Handle error loading bitmap
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    if(!plancheSprites_originale_formatted) {
        // Handle error converting bitmap
        std::cerr << "Failed to convert bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
}

GameView::~GameView() {
    // Clean up game view related data here
    SDL_FreeSurface(plancheSprites_prof);
    SDL_FreeSurface(plancheSprites_originale);
    SDL_FreeSurface(plancheSprites_originale_formatted);
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

    // Update the top_left_position of the ghost sprite based on the CharacterState
    SDL_Rect ghost_sprite({ state.top_left_position.x,state.top_left_position.y, 42,42 }); // ici scale x2

    // ici on change entre les 2 sprites sources pour une jolie animation.
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite_in.x += 17;
    }



    // couleur transparente
    SDL_SetColorKey(plancheSprites_originale_formatted, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites_originale_formatted, &ghost_sprite_in, win_surf, &ghost_sprite);
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

    // Update the top_left_position of the ghost sprite based on the CharacterState
    SDL_Rect pacman_sprite({ state.top_left_position.x,state.top_left_position.y, 39,39 }); // ici scale x2

    // // ici on change entre les 2 sprites sources pour une jolie animation.
    // if ((gameModel.getCount() / 4) % 2) {
    //     pacman_sprite_in.x += 17;
    // }

    // couleur transparente
    SDL_SetColorKey(plancheSprites_originale_formatted, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites_originale_formatted, &pacman_sprite_in, win_surf, &pacman_sprite);
}

void GameView::renderMaze() {
    SDL_SetColorKey(plancheSprites_originale_formatted, false, 0);

    if(SDL_BlitScaled(plancheSprites_originale_formatted, &map_sprite_originale, win_surf, &bg)<0){
        printf("SDL_BlitScaled failed: %s\n", SDL_GetError());
    }
}

void GameView::renderHUD() {
    SDL_Rect pacman_l_medium_sprite= gameModel.getPacMan().getSpriteL();

    SDL_SetColorKey(plancheSprites_prof, true, 0);
    SDL_BlitScaled(plancheSprites_prof, &zero_sprite, win_surf, &first_score_number_pos);
    SDL_BlitScaled(plancheSprites_prof, &zero_sprite, win_surf, &second_score_number_pos);
    SDL_BlitScaled(plancheSprites_prof, &one_sprite, win_surf, &one_up_one_pos);
    SDL_BlitScaled(plancheSprites_prof, &U_sprite, win_surf, &one_up_U_pos);
    SDL_BlitScaled(plancheSprites_prof, &P_sprite, win_surf, &one_up_P_pos);
    SDL_BlitScaled(plancheSprites_prof, &pacman_l_medium_sprite, win_surf, &first_life_pos);
    SDL_BlitScaled(plancheSprites_prof, &pacman_l_medium_sprite, win_surf, &second_life_pos);
    SDL_BlitScaled(plancheSprites_prof, &pacman_l_medium_sprite, win_surf, &third_life_pos);
}
