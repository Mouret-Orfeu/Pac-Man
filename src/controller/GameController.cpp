#include "GameController.h"
#include "model/GameModel.h"
#include "view/GameView.h"
#include "model/Ghost.h"

#include <SDL.h>
#include <iostream>

GameController::GameController() : sdl_initialized(false) {}

GameController::~GameController() {
    if (sdl_initialized) {
        SDL_Quit();
    }
}

bool GameController::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
        return false;
    }
    sdl_initialized = true;
    return true;
}

void GameController::run() {
    if (!sdl_initialized) {
        return;
    }

    GameModel gameModel;
    GameView gameView(gameModel);

    // Main game loop
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			default: break;
			}
		}

        // Gestion du clavier
        int nbk;
        const Uint8* keys = SDL_GetKeyboardState(&nbk);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT])
            puts("LEFT");
        if (keys[SDL_SCANCODE_RIGHT])
            puts("RIGHT");
        if (keys[SDL_SCANCODE_UP])
            puts("UP");
        if (keys[SDL_SCANCODE_DOWN])
            puts("DOWN");

        gameModel.update();

        // AFFICHAGE
		gameView.draw();
        // LIMITE A 60 FPS
		SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
	}
}
