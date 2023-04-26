#include <SDL.h>
#include <iostream>
#include "view.h"
#include "characters.h"
#include "controller.h"


//count est provisoir, le temps qu'on garde le fantome qui tourne en rond
int count;

int main(int argc, char** argv)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
		return 1;
    }

	view::init(count);
    // BOUCLE PRINCIPALE

	SDL_Point init_pacman_position={pacman_init_pos.x, pacman_init_pos.y};

	Main_character pacman(init_pacman_position);


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

       //Gestion des input au clavier
        //controller::check_escap(quit);
//
		//controller::direction_t direction= controller::check_input();
		//pacman.set_direction(direction);

		int nbk;
    	const Uint8* keys = SDL_GetKeyboardState(&nbk);

		controller::direction_t direction=controller::none;

		if (keys[SDL_SCANCODE_ESCAPE])
        	quit = true;
		if (keys[SDL_SCANCODE_LEFT])
        	direction= controller::left;
    	if (keys[SDL_SCANCODE_RIGHT])
    	    direction= controller::right;
    	if (keys[SDL_SCANCODE_UP])
    	    direction= controller::up;
    	if (keys[SDL_SCANCODE_DOWN])
    	    direction= controller::down;

		pacman.set_direction(direction);


		pacman.move();

		SDL_Point pacman_position= pacman.get_position();

    
        //Affichage (pour l'instant ça affiche la map et le fantome qui tourne en rond)
        view::update_display(count, pacman_position);

	}
    SDL_Quit(); // ON SORT

    return 0;
}