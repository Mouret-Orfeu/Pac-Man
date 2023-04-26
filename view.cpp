#include <view.h>


int map_top_left_x_coord = WIN_WIDTH - MAP_WIDTH;

const SDL_Rect src_bg = { 200,3, 168,216 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { map_top_left_x_coord,4, 672,864 }; // ici sca

SDL_Rect pacman_medium_r= {18, 88, 16, 16};
SDL_Rect pacman_init_pos = { map_top_left_x_coord+34,34,32,32 };

SDL_Rect red_ghost_r = { 3,123, 16,16 }; 
SDL_Rect red_ghost_l = { 37,123, 16,16 }; 
SDL_Rect red_ghost_d = { 105,123, 16,16 }; 
SDL_Rect red_ghost_u = { 71,123, 16,16 }; 
SDL_Rect red_ghost_pos = { map_top_left_x_coord+34,34, 32,32 };   // ici sca

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;



/*************************************************************************/

void view::init(int& count)
{

	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!pWindow)
	{
		printf("Failed to open %d x %d window: %s\n", WIN_WIDTH, WIN_HEIGHT, SDL_GetError());
		exit(1);
	}
    //////////////////////

	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    count = 0;

}


/*************************************************************************/


// fonction qui met à jour la surface de la fenetre "win_surf"
void view::draw(int& count, SDL_Point pacman_position)
{
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg); 

    // petit truc pour faire tourner le fantome
    //change l'image du fantome pour le faire regarder dans les bonnes direction (_r=right, _l=left, _d=down, _u=up)
    //et fait bouger le fantome dans la bonne direction
    //pour l'instant le fantome tourne toutes les 128 frames, et fait 1 pixel par frame 
    SDL_Rect* ghost_in = nullptr;
    switch (count/128)
    {
        case 0:
            ghost_in = &(red_ghost_r);
            red_ghost_pos.x++;
            break;
        case 1:
            ghost_in = &(red_ghost_d);
            red_ghost_pos.y++;
            break;
        case 2:
            ghost_in = &(red_ghost_l);
            red_ghost_pos.x--;
            break;
        case 3:
            ghost_in = &(red_ghost_u);
            red_ghost_pos.y--;
            break;
    }
    count =(count+1)%(512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count/4)%2)
        ghost_in2.x += 17;
        
    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    
    // copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &red_ghost_pos);

    SDL_Rect pacman_pos_rect = { pacman_position.x,pacman_position.y,32,32 };

    //on affiche aussi pacman
    SDL_BlitScaled(plancheSprites, &pacman_medium_r, win_surf, &pacman_pos_rect);

}


/*************************************************************************/


void view::update_display(int& count, SDL_Point pacman_position)
{
    // AFFICHAGE
	draw(count, pacman_position);
	SDL_UpdateWindowSurface(pWindow); 
    // LIMITE A 60 FPS
    // utiliser SDL_GetTicks64() pour plus de precisions (affichage toutes les 16 ms) (attention à mettre le bon delai)
    //mettre ce qu'il faut pour avoir 60 fps
	SDL_Delay(16); 
}

/*Pour avoir 60FPS, à la place de SDL_Delay(16) on peut écrire
```
then = SDL_GetTicks();
remainder = 0;
capFrameRate(&then, &remainder)

//avec la fonction capFrameRate qui est définie comme suit:

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;
	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();
}*/

