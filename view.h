#ifndef VIEW
#define VIEW

#include <SDL.h>

using namespace std;

# define WIN_WIDTH 800
# define WIN_HEIGHT 900

# define MAP_WIDTH 672
# define MAP_HEIGHT 864

extern int map_top_left_x_coord;

extern const SDL_Rect src_bg; // x,y, w,h (0,0) en haut a gauche
extern SDL_Rect bg; // ici sca

extern SDL_Rect pacman_medium_r;
extern SDL_Rect pacman_init_pos;

extern SDL_Rect red_ghost_r; 
extern SDL_Rect red_ghost_l; 
extern SDL_Rect red_ghost_d; 
extern SDL_Rect red_ghost_u; 
extern SDL_Rect red_ghost_pos;   // ici sca

extern SDL_Window* pWindow;
extern SDL_Surface* win_surf;
extern SDL_Surface* plancheSprites;


namespace view
{

    /**
    * @brief initialise la fenêtre et la surface d'affichage et load le sprite de la map pacman
    * 
    * @param count est un compteur qui sert pour l'instant à boucler le mouvement du fantome 
    */
    void init(int& count);


    /**
    * @brief met à jour la surface de la fenetre "win_surf"
    * 
    */
    void draw(int& count, SDL_Point pacman_position);


    /**
    * @brief Met à jour l'affichage avec tous ses elements
    * 
    */
    void update_display(int& count, SDL_Point pacman_position);
}

#endif