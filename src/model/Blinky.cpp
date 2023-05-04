#include "Blinky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "common/Tile.h"
#include "GameModel.h"
#include "Ghost.h"

#include <vector>
#include <iostream>
#include <algorithm>

const Position init_pos_Blinky = Position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Blinky = {0,WINDOW_COLS-3};

Blinky::Blinky(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::BLINKY, init_pos_Blinky, Direction::LEFT, scatter_target_tile_Blinky)
{}

Blinky::~Blinky() {
    // Clean up Blinky-specific data here
}

void Blinky::updateDirection() {

    bool forbiden_tile_up= false;
    bool forbiden_tile_down= false;

    //On va stoquer les tiles prochaines tiles qui ne sont pas des murs
    std::vector<Direction> next_legal_direction;

    for (Direction d : {Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT}) {
        //Les fantomes ne font pas demi tour en état normal
        if (d != direction) {

            Tile next_possible_tile;
            
            if(gameModel.isTileLegal(next_possible_tile)){
                auto iter_1 = std::find(forbiden_tiles_UP.begin(), forbiden_tiles_UP.end(), next_possible_tile);
                auto iter_2 = std::find(forbiden_tiles_DOWN.begin(), forbiden_tiles_DOWN.end(), next_possible_tile);
                if(iter_1 != forbiden_tiles_UP.end())
                    forbiden_tile_up=true;
                if(iter_2 != forbiden_tiles_DOWN.end())
                    forbiden_tile_down=true;

                next_legal_direction.push_back(d);
            }
        }
    }
    int nb_legal_direction=next_legal_direction.size();

    //Si le tournant n'a qu'un issue, le fantome prend la direction correspondante
    if(nb_legal_direction == 1){
        direction = next_legal_direction[0];
    }
    /*Si le tournant est un carrefour (plusieurs issues possibles), 
    on calcule la distance de la tile sortante de chaque issue à la target tile, et on choisit la direction qui minimise cette distance*/
    std::vector<Direction> best_directions;
    if(nb_legal_direction>1 && nb_legal_direction<5)
    {
        int min_distance=WINDOW_ROWS*WINDOW_COLS;

        /*best_directions va stoquer la directions des prochaines tile apres le carrefour,
        dont la distance à la target tile est minimale (les tiles à égalité)*/
        
        for(Direction d : next_legal_direction){

            /*On vérifie que la direction n'est pas celle d'une tile interdite 
            (ily a des tiles (non mur) qui sont interdites dans certaines directions)*/
            Tile next_possible_tile=position.getNextTile(d);
            if(position.distance_tile(next_possible_tile, current_target_tile)<min_distance && !(forbiden_tile_down && d==Direction::DOWN) && !(forbiden_tile_up && d==Direction::UP)){
                best_directions.clear();
                best_directions.push_back(d);
            }
            if(position.distance_tile(next_possible_tile, current_target_tile)==min_distance && !(forbiden_tile_down && d==Direction::DOWN) && !(forbiden_tile_up && d==Direction::UP)){
                best_directions.push_back(d);
            }
        }
    }
    else{
        //message d'erreur
        std::cout<<"Erreur : Blinky a 0 ou plus de 4 direction possibles"<<std::endl;
        exit(1);
    }

    //On choisit la direction qui minimise la distance à la target tile, si égalité, se référer à l'ordre de priorité (compareDirections)
    std::sort(best_directions.begin(), best_directions.end(), compareDirections);
    direction = best_directions[0];


}

void Blinky::move(int count) {
    (void)count;

    if(position.isCenteredOnTile()){
        updateDirection();
    }

    updatePosition();
}
