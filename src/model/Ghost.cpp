#include "Ghost.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "PacMan.h"
#include "MonsterDen.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <set>

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile, bool out_of_den, bool can_leave_den, PacMan& pacman)
:Character(gameModel, initial_position, direction),
 ghost_type(ghost_type),
 ghost_mode(Mode::SCATTER),
 scatter_target_tile(scatter_target_tile),
 out_of_den(out_of_den),
 can_leave_den(can_leave_den),
 current_target_tile(scatter_target_tile),
 out_of_den_position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2),
 center_den_position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2),
 pacman(pacman),
 mode_has_changed(false),
 mode_just_changed(false)
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

    if(mode_just_changed==true)
    {
        direction=getOppositeDirection(direction);
        mode_just_changed=false;

        //DEBUG
        //std::cout<<"mod_just_changed"<<std::endl;
    }

    /*Ghosts use a random number generator to pick a way to turn at each intersection when frightened.
     If the tile of the chosen direction is not legal, the ghost then test the legality of the tiles in that order of direction: up, left, down, and right an choose the direction of the first legal tile found*/
    if(ghost_mode==Ghost::Mode::FRIGHTENED)
    {
        //En mode FRIGTHENED, les fantomes se déplacent aléatoirement (mais toujours avec la même seed)
        int random=rand()%3;

        //on extrait les direction qui ne sont pas l'opposé de la direction actuelle
        std::vector<Direction> not_turnaround_directions={Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT};
        not_turnaround_directions.erase(std::remove(not_turnaround_directions.begin(), not_turnaround_directions.end(), getOppositeDirection(direction)), not_turnaround_directions.end());

        //Si la direction aléatoire est légale (pas un mur) on la choisit        
        if(gameModel.isTileLegal(position.getNextTile(not_turnaround_directions[random]))){

            direction=not_turnaround_directions[random];
            return;
        }
        //Si la direction aléatoire est bloqué par un mur (donc illégal) on choisit la direction légal par ordre de preference up, left, down, right (sans faire demi tour) 
        else{
            for (Direction d : {Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT}) {
                if (d != getOppositeDirection(direction)) {
                    if (gameModel.isTileLegal(position.getNextTile(d))) {
                        direction=d;
                        return;
                    }
                }
            }
        }
    }



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
        int min_distance=2*WINDOW_ROWS*WINDOW_COLS;

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

void Ghost::setModeHasChanged(bool mod_has_changed)
{
    this->mode_has_changed=mod_has_changed;
}

bool Ghost::getModeHasChanged() const
{
    return mode_has_changed;
}

void Ghost::setModeJustChanged(bool mod_just_changed)
{
    this->mode_just_changed=mod_just_changed;
}

bool Ghost::getModeJustChanged() const
{
    return mode_just_changed;
}

void Ghost::setPreviousMode(Mode previous_ghost_mode)
{
    this->previous_ghost_mode=previous_ghost_mode;
}

Ghost::Mode Ghost::getPreviousMode() const
{
    return previous_ghost_mode;
}

bool Ghost::isOutOfDen()
{
    return out_of_den;
}

void Ghost::move(int count) {
    (void)count;

    updateTargetTile();

    if(out_of_den==false && can_leave_den==true)
    {
        leaveTheDen();
    }

    if(position.isCenteredOnTile() && out_of_den==true){
        //DEBUG
        //printDirection(direction);
        
        updateDirection();
    }

    if(can_leave_den==true){
        updatePosition();
    }
}