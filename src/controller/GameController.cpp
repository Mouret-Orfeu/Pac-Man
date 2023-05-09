#include "GameController.h"
#include "model/GameModel.h"
#include "view/GameView.h"
#include "model/Ghost.h"
#include "model/PacMan.h"
#include "model/Character.h"
#include "common/Direction.h"

#include <SDL.h>
#include <iostream>
#include <cmath>

GameController::GameController()
:sdl_initialized(false),
 gameModel(),
 gameView(gameModel)
{}

GameController::~GameController() {
    if (sdl_initialized)
        SDL_Quit();
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

    // Main game loop
    int frame_count_game_over = 0;
	bool quit = false;
    Uint64 frameStartTime = SDL_GetTicks64();
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

        Direction input_direction = Direction::NONE;
        if (keys[SDL_SCANCODE_LEFT])
            input_direction = Direction::LEFT;
        if (keys[SDL_SCANCODE_RIGHT])
            input_direction = Direction::RIGHT;
        if (keys[SDL_SCANCODE_UP])
            input_direction = Direction::UP;
        if (keys[SDL_SCANCODE_DOWN])
            input_direction = Direction::DOWN;


        if(input_direction != Direction::NONE)
            gameModel.setStartState(false);

        if(!gameModel.getStartState() && !gameModel.getGameOverState()){
            //là dedans y'a move pour tous les persos
            gameModel.update(input_direction);
        }
        

        // AFFICHAGE
        gameView.draw();

        //Apres 1 secondes (120 frames) d'affichage de game over on passe dans l'etat start
        if(gameModel.getGameOverState()){
            frame_count_game_over++;
            if(frame_count_game_over == 60){
                gameModel.setGameOverState(false);
                frame_count_game_over = 0;
                gameModel.setStartState(true);
            }
                
        };

        //Animation de la mort
        if (gameModel.getPacMan().isGameOver()) {
            int slowdown_factor = 8;
            for (int i = 0; i < slowdown_factor*11; i++) {
                int death_sprite_num = i / slowdown_factor;
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
                const Uint8* keys = SDL_GetKeyboardState(nullptr);
                if (keys[SDL_SCANCODE_ESCAPE])
                    quit = true;

                if (quit)
                    break;

                // AFFICHAGE
                gameView.drawDeathAnimation(death_sprite_num);

                // LIMITE A 60 FPS
                limitFramerate(frameStartTime);
            }
            
            gameModel.getPacMan().setPosition(gameModel.getPacMan().getSpawnPos());
            gameModel.getPacMan().setIsGameOver(false);
            if(gameModel.getPacMan().getLives() == -1){
                gameModel.setGameOverState(true);
                gameModel.resetTilesMatrix();
            }
                
        }

        // LIMITE A 60 FPS
        limitFramerate(frameStartTime);
	}
}

void GameController::limitFramerate(Uint64& frameStartTime) {
    const Uint64 desiredFrameTime = 1000 / 60; // 60 FPS -> 1000 ms for 60 frames
    Uint64 currentTime = SDL_GetTicks64();
    Uint64 elapsedTime = currentTime - frameStartTime;
    if (elapsedTime < desiredFrameTime) {
        SDL_Delay(static_cast<Uint32>(desiredFrameTime - elapsedTime));
    }
    frameStartTime = SDL_GetTicks64();
}
