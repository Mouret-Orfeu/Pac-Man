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
    SDL_Rect ghost_sprite_in;
    CharacterState state = ghost.getState();
    switch (state.direction) {
        case CharacterDirection::RIGHT:
            ghost_sprite_in = Blinky_sprite_r;
            break;
        case CharacterDirection::DOWN:
            ghost_sprite_in = Blinky_sprite_d;
            break;
        case CharacterDirection::LEFT:
            ghost_sprite_in = Blinky_sprite_l;
            break;
        case CharacterDirection::UP:
            ghost_sprite_in = Blinky_sprite_u;
            break;
    }

    // Update the top_left_position of the ghost sprite based on the CharacterState
    SDL_Rect ghost_sprite({ state.top_left_position.x,state.top_left_position.y, 42,42 }); // ici scale x2

    // ici on change entre les 2 sprites sources pour une jolie animation.
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite_in.x += 16;
    }



    // couleur transparente
    SDL_SetColorKey(spriteSheet_Namco_formatted, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(spriteSheet_Namco_formatted, &ghost_sprite_in, win_surf, &ghost_sprite);
}

void GameView::render(const PacMan& pacman) {
    // petit truc pour faire tourner le fantome
    SDL_Rect pacman_sprite_in;
    CharacterState state = pacman.getState();
    switch (state.direction) {
        case CharacterDirection::RIGHT:
            pacman_sprite_in = pacman_sprite_r;
            break;
        case CharacterDirection::DOWN:
            pacman_sprite_in = pacman_sprite_d;
            break;
        case CharacterDirection::LEFT:
            pacman_sprite_in = pacman_sprite_l;
            break;
        case CharacterDirection::UP:
            pacman_sprite_in = pacman_sprite_u;
            break;
        case CharacterDirection::NONE:
            // TODO: set sprite to round sprite
            pacman_sprite_in = pacman_sprite_r;
            break;
    }

    // Update the top_left_position of the ghost sprite based on the CharacterState
    SDL_Rect pacman_sprite({ state.top_left_position.x,state.top_left_position.y, 39,39 }); // ici scale x2

    // // ici on change entre les 2 sprites sources pour une jolie animation.
    // if ((gameModel.getCount() / 4) % 2) {
    //     pacman_sprite_in.x += 17;
    // }

    // couleur transparente
    SDL_SetColorKey(spriteSheet_Namco_formatted, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_sprite_in, win_surf, &pacman_sprite);
}

void GameView::renderMaze() {
    SDL_SetColorKey(spriteSheet_Namco_formatted, false, 0);

    if(SDL_BlitScaled(spriteSheet_Namco_formatted, &map_sprite_originale, win_surf, &bg)<0){
        printf("SDL_BlitScaled failed: %s\n", SDL_GetError());
    }
}

void GameView::renderHUD() {
    SDL_SetColorKey(spriteSheet_NES, true, 0);

    // Score
    SDL_BlitScaled(spriteSheet_NES, &zero_sprite, win_surf, &first_score_number_pos);
    SDL_BlitScaled(spriteSheet_NES, &zero_sprite, win_surf, &second_score_number_pos);

    // 1UP
    SDL_BlitScaled(spriteSheet_NES, &one_sprite, win_surf, &one_up_one_pos);
    SDL_BlitScaled(spriteSheet_NES, &U_sprite, win_surf, &one_up_U_pos);
    SDL_BlitScaled(spriteSheet_NES, &P_sprite, win_surf, &one_up_P_pos);

    // Lives
    SDL_SetColorKey(spriteSheet_Namco_formatted, true, 0);
    SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &first_life_pos);
    SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &second_life_pos);
    SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &third_life_pos);
}
