#include "Ghost.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "PacMan.h"

#include <iostream>
#include <algorithm>

//Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation)
//:Character(gameModel, initial_position, direction, sprite_orientation),
// ghost_type(ghost_type),
//{}

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile, bool out_of_den, PacMan& pacman)
:Character(gameModel, initial_position, direction),
 ghost_type(ghost_type),
 ghost_mode(Mode::SCATTER),
 scatter_target_tile(scatter_target_tile),
 current_target_tile(scatter_target_tile),
 out_of_den_position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2),
 center_den_position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2),
 pacman(pacman)
{}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

Ghost::Type Ghost::getType() const {
    return ghost_type;
}

Ghost::Mode Ghost::getMode() const {
    return ghost_mode;
}

Tile Ghost::getScatterTargetTile() const
{
    return scatter_target_tile;
}

void Ghost::setMode(Mode mode)
{
    ghost_mode=mode;
}

void Ghost::setCurrentTargetTile(Tile tile)
{
    current_target_tile=tile;
}

Tile Ghost::getCurrentTargetTile() const
{
    return current_target_tile;
}

void Ghost::printType(Ghost::Type ghost_type) const
{


    switch (ghost_type)
    {
    case Ghost::Type::BLINKY:
        std::cout << "BLINKY";
        break;
    case Ghost::Type::PINKY:
        std::cout << "PINKY";
        break;
    case Ghost::Type::INKY:
        std::cout << "INKY";
        break;
    case Ghost::Type::CLYDE:
        std::cout << "CLYDE";
        break;
    default:
        std::cout << "ERROR printType()";
        break;
    }
}



void Ghost::updateDirection() {

    bool forbiden_tile_up= false;
    bool forbiden_tile_down= false;

    //On va stoquer les tiles prochaines tiles qui ne sont pas des murs
    std::vector<Direction> next_legal_directions;

    for (Direction d : {Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT}) {
        //Les fantomes ne font pas demi tour en état normal
        if (d != getOppositeDirection(direction)) {

            //DEBUG
            //printDirection(d);
            //printDirection(direction);
            //std::cout<<std::endl;
            //std::cout<<std::endl;
            //std::cout<<std::endl;




            Tile next_possible_tile=position.getNextTile(d);
            
            if(gameModel.isTileLegal(next_possible_tile)){
                auto iter_1 = std::find(forbiden_tiles_UP.begin(), forbiden_tiles_UP.end(), next_possible_tile);
                auto iter_2 = std::find(forbiden_tiles_DOWN.begin(), forbiden_tiles_DOWN.end(), next_possible_tile);
                if(iter_1 != forbiden_tiles_UP.end())
                    forbiden_tile_up=true;
                if(iter_2 != forbiden_tiles_DOWN.end())
                    forbiden_tile_down=true;

                next_legal_directions.push_back(d);
                
            }
        }
    }

    
    //DEBUG
    //std::cout<<std::endl;
    ////loop on next_legal_directions and printDirection()
    //std::cout << "next_legal_directions (avans filtrage) : ";
    //for(Direction d : next_legal_directions){
    //    printDirection(d);
    //}
    //std::cout << std::endl<<std::endl;

    int nb_legal_direction=next_legal_directions.size();



    //DEBUG
    //print all the legal direction
    //std::cout << "next_legal_directions : "<<std::endl;
    //for(Direction d : next_legal_directions){
    //    printDirection(d);
    //    std::cout << std::endl;
    //}

    //Si le tournant n'a qu'un issue, le fantome prend la direction correspondante
    if(nb_legal_direction == 1){
        //DEBUG
        //std::cout<<"seule direction possible: "<<std::endl;
        //printDirection(next_legal_directions[0]);

        direction = next_legal_directions[0];
        return;
    }
    /*Si le tournant est un carrefour (plusieurs issues possibles), 
    on calcule la distance de la tile sortante de chaque issue à la target tile, et on choisit la direction qui minimise cette distance*/
    std::vector<Direction> best_directions;
    if(nb_legal_direction>1 && nb_legal_direction<5)
    {
        //Distance la plus grandethéorique sur notre fenêtre
        int min_distance=WINDOW_ROWS*WINDOW_COLS;

        /*best_directions va stoquer la directions des prochaines tile apres le carrefour,
        dont la distance à la target tile est minimale (les tiles à égalité)*/
        
        for(Direction d : next_legal_directions){

            /*On vérifie que la direction n'est pas celle d'une tile interdite 
            (ily a des tiles (non mur) qui sont interdites dans certaines directions)*/
            Tile next_possible_tile=position.getNextTile(d);
            if(position.distance_tile(next_possible_tile, current_target_tile)<min_distance && !(forbiden_tile_down && d==Direction::DOWN) && !(forbiden_tile_up && d==Direction::UP)){
                best_directions.clear();
                best_directions.push_back(d);

                min_distance=position.distance_tile(next_possible_tile, current_target_tile);
            }
            else if(position.distance_tile(next_possible_tile, current_target_tile)==min_distance && !(forbiden_tile_down && d==Direction::DOWN) && !(forbiden_tile_up && d==Direction::UP)){
                best_directions.push_back(d);
            }
        }

        //DEBUG
        //std::cout<<nb_legal_direction<<" directions possibles (apres filtrage): "<<std::endl;
        //for(Direction d : best_directions){
        //    printDirection(d);
        //    
        //}
    }
    else if(nb_legal_direction==0){
        //message d'erreur
        std::cout<<"Erreur :";
        printType(ghost_type);
        std::cout<<" a 0 direction possibles"<<std::endl;
        exit(1);
    }
    else{
        //message d'erreur
        std::cout<<"Erreur :";
        printType(ghost_type);
        std::cout<<" a plus de 4 direction possibles"<<std::endl;
        exit(1);
    }

    //On choisit la direction qui minimise la distance à la target tile, si égalité, se référer à l'ordre de priorité (compareDirections)
    std::sort(best_directions.begin(), best_directions.end(), compareDirections);
    direction = best_directions[0];

    //DEBUG
    //std::cout << "Direction choisie : ";
    //printDirection(direction);
    return;


}