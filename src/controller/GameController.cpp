#include "GameController.h"
#include "model/GameModel.h"
#include "view/GameView.h"
#include "model/Ghost.h"
#include "model/PacMan.h"
#include "model/Character.h"

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
	while (!quit) {
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			default: break;
			}
		}

        // Gestion du clavier
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        Character::Direction input_direction = Character::Direction::NONE;
        if (keys[SDL_SCANCODE_LEFT])
            input_direction = Character::Direction::LEFT;
        if (keys[SDL_SCANCODE_RIGHT])
            input_direction = Character::Direction::RIGHT;
        if (keys[SDL_SCANCODE_UP])
            input_direction = Character::Direction::UP;
        if (keys[SDL_SCANCODE_DOWN])
            input_direction = Character::Direction::DOWN;

        //là dedans y'a move pourtous les persos
        gameModel.update(input_direction);

        // AFFICHAGE
		gameView.draw();

        //SDL_Delay(5000);

        //Animation de la mort
        if (gameModel.getDeath()) {
            int death_sprite_count = 0;
            while (gameModel.getDeath())
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

                // AFFICHAGE
	        	gameView.draw_death(death_sprite_count);

                // LIMITE A 60 FPS
                const Uint64 desiredFrameTime = 16; // 60 FPS = 1000 ms -> ~16 ms per frame
                Uint64 currentTime = SDL_GetTicks64();
                Uint64 frameStartTime = currentTime;
                Uint64 elapsedTime = currentTime - frameStartTime;
                if (elapsedTime < desiredFrameTime) {
                    SDL_Delay(static_cast<Uint32>(desiredFrameTime - elapsedTime));
                }
                frameStartTime = SDL_GetTicks64();

                if(death_sprite_count==11){
                    gameModel.setDeath(false);
                }

                death_sprite_count++;
            

            }

        }

    

        // LIMITE A 60 FPS
        const Uint64 desiredFrameTime = 16; // 60 FPS = 1000 ms -> ~16 ms per frame
        Uint64 currentTime = SDL_GetTicks64();
        Uint64 frameStartTime = currentTime;
        Uint64 elapsedTime = currentTime - frameStartTime;
        if (elapsedTime < desiredFrameTime) {
            SDL_Delay(static_cast<Uint32>(desiredFrameTime - elapsedTime));
        }
        frameStartTime = SDL_GetTicks64();
	}

}   