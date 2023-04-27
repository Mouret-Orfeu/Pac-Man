#include "GameView.h"
#include "model/GameModel.h"
#include "model/Character.h"
#include "model/Ghost.h"

#include <SDL.h>
#include <iostream>

int WINDOW_WIDTH= 28*TILE_SIZE;
int WINDOW_HEIGHT= 36*TILE_SIZE;
int MAP_WIDTH= 28*TILE_SIZE;
int MAP_HEIGHT= 31*TILE_SIZE;

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites_prof = nullptr;
SDL_Surface* plancheSprites_originale = nullptr;

SDL_Point map_top_left={0,48};

SDL_Rect map_sprite_originale = { 0,0, 224,248 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect map_sprite_prof ={ 200,3, 168,216 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect zero_sprite = { 3,52, 8,8 }; 
SDL_Rect one_sprite = { 12,52, 7,8 };
SDL_Rect U_sprite = { 43,68, 9,8 };  
SDL_Rect P_sprite = { 3,68, 8,8 }; 

SDL_Rect bg = { 0,3*TILE_SIZE,224*3,248*3 }; 
SDL_Rect first_score_number_pos = { 5*TILE_SIZE,TILE_SIZE, TILE_SIZE-2,TILE_SIZE-2};
SDL_Rect second_score_number_pos = { 6*TILE_SIZE,TILE_SIZE, TILE_SIZE-2,TILE_SIZE-2};
SDL_Rect one_up_one_pos = { 3*TILE_SIZE,0, TILE_SIZE-2,TILE_SIZE-2};
SDL_Rect one_up_U_pos = { 4*TILE_SIZE,0, TILE_SIZE-2,TILE_SIZE-2};
SDL_Rect one_up_P_pos = { 5*TILE_SIZE,0, TILE_SIZE-2,TILE_SIZE-2};
SDL_Rect first_life_pos = { 2*TILE_SIZE,WINDOW_HEIGHT-2*TILE_SIZE, 2*TILE_SIZE-5,2*TILE_SIZE-5};
SDL_Rect second_life_pos = { 4*TILE_SIZE,WINDOW_HEIGHT-2*TILE_SIZE, 2*TILE_SIZE-5,2*TILE_SIZE-5};
SDL_Rect third_life_pos = { 6*TILE_SIZE,WINDOW_HEIGHT-2*TILE_SIZE, 2*TILE_SIZE-5,2*TILE_SIZE-5};



GameView::GameView(GameModel& gameModel) : gameModel(gameModel) {
    // Initialize game view related data here
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH , WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

    //On utilise des sprites venant des ces 2 fichiers
	plancheSprites_prof = SDL_LoadBMP("./pacman_sprites.bmp");
    plancheSprites_originale = SDL_LoadBMP("./pacman_sprites_original.bmp");

    if ((!plancheSprites_prof) || (!plancheSprites_originale)) {
        // Handle error loading bitmap
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
}

GameView::~GameView() {
    // Clean up game view related data here
    SDL_FreeSurface(plancheSprites_prof);
    SDL_FreeSurface(plancheSprites_originale);
    SDL_DestroyWindow(pWindow);
}

void GameView::draw() {

    SDL_Rect pacman_l_medium_sprite= gameModel.getPacMan().getSpriteL();

    // Move the draw() function contents here
    SDL_SetColorKey(plancheSprites_originale, false, 0);

    SDL_Surface*  plancheSprites_originale_formatted= SDL_ConvertSurface(plancheSprites_originale, win_surf->format, 0);
    if(SDL_BlitScaled(plancheSprites_originale_formatted, &map_sprite_originale, win_surf, &bg)<0){
        printf("SDL_BlitScaled failed: %s\n", SDL_GetError());
    }

    SDL_SetColorKey(plancheSprites_prof, true, 0);
    SDL_BlitScaled(plancheSprites_prof, &zero_sprite, win_surf, &first_score_number_pos);
    SDL_BlitScaled(plancheSprites_prof, &zero_sprite, win_surf, &second_score_number_pos);
    SDL_BlitScaled(plancheSprites_prof, &one_sprite, win_surf, &one_up_one_pos);
    SDL_BlitScaled(plancheSprites_prof, &U_sprite, win_surf, &one_up_U_pos);
    SDL_BlitScaled(plancheSprites_prof, &P_sprite, win_surf, &one_up_P_pos);
    SDL_BlitScaled(plancheSprites_prof, &pacman_l_medium_sprite, win_surf, &first_life_pos);
    SDL_BlitScaled(plancheSprites_prof, &pacman_l_medium_sprite, win_surf, &second_life_pos);
    SDL_BlitScaled(plancheSprites_prof, &pacman_l_medium_sprite, win_surf, &third_life_pos);

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
    SDL_Rect ghost_sprite({ state.top_left_position.x,state.top_left_position.y, 32,32 }); // ici scale x2

    // ici on change entre les 2 sprites sources pour une jolie animation.
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite_in.x += 17;
    }

    // couleur transparente
    SDL_SetColorKey(plancheSprites_prof, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites_prof, &ghost_sprite_in, win_surf, &ghost_sprite);
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
    SDL_Rect pacman_sprite({ state.top_left_position.x,state.top_left_position.y, 32,32 }); // ici scale x2

    // // ici on change entre les 2 sprites sources pour une jolie animation.
    // if ((gameModel.getCount() / 4) % 2) {
    //     pacman_sprite_in.x += 17;
    // }

    // couleur transparente
    SDL_SetColorKey(plancheSprites_prof, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites_prof, &pacman_sprite_in, win_surf, &pacman_sprite);
    

}
