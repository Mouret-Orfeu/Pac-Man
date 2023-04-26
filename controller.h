#ifndef CONTROLLER
#define CONTROLLER

#include <SDL.h>
#include <iostream>

using namespace std;



namespace controller
{
    typedef enum direction_t
    {
        up,
        down,
        left,
        right,
        none,
    }direction_t;

    /**
    * @brief  Gère les input en verifiant l'état du clavier (on utilise pas les evenements claviers), puis traite ces input (à compléter plus tard) 
    * 
    * @param quit vaut true quand on appuiera sur echap, pour fermer le programe  
    * 
    */
    direction_t check_input();

    /**
    * @brief  check si on a appuyé sur echap
    * 
    * @param quit vaut true quand on appuiera sur echap, pour fermer le programe  
    * 
    */
    void check_escap(bool& quit);
}

#endif