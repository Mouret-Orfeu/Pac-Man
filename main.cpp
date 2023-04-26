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
        controller::check_escap(quit);

		controller::direction_t direction= controller::check_input();
		pacman.set_direction(direction);

		//DEBUG
		switch (direction)
    	{
    	    case controller::left:
    	        cout<<"left"<<endl;
    	        break;
    	    case controller::right:
    	        cout<<"right"<<endl;
    	        break;
    	    case controller::up:
    	        cout<<"up"<<endl;
    	        break;
    	    case controller::down:
    	        cout<<"down"<<endl;
    	        break;
    	    case controller::none:
				cout<<"none"<<endl;
    	        break;
    	}

		pacman.move();

		SDL_Point pacman_position= pacman.get_position();

    
        //Affichage (pour l'instant ça affiche la map et le fantome qui tourne en rond)
        view::update_display(count, pacman_position);

	}
    SDL_Quit(); // ON SORT

    return 0;
}