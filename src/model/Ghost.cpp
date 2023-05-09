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
#include <random>

Ghost::Ghost(GameModel& game_model, Ghost::Type ghost_type, Position spawn_position, Position respawn_position, Direction spawn_direction, Tile scatter_target_tile, bool out_of_den, PacMan& pacman, MonsterDen& monster_den)
:Character(game_model, spawn_position, spawn_direction),
 ghost_type(ghost_type),
 ghost_mode(Mode::SCATTER),
 scatter_target_tile(scatter_target_tile),
 out_of_den(out_of_den),
 current_target_tile(scatter_target_tile),
 forbiden_tiles_UP({{13,12},{13,15}}),
 forbiden_tiles_DOWN({{25,12},{25,15}}),
 Slowing_tile_right({17,22}),
 Slowing_tile_left({17,5}),
 out_of_den_position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2),
 center_den_position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2),
 pacman(pacman),
 monster_den(monster_den),
 mode_has_changed(false),
 mode_just_changed(false),
 spawn_direction(spawn_direction),
 spawn_position(spawn_position),
 respawn_position(respawn_position),
 normal_speed(75),
 is_in_tunnel(false),
 normal_speed_changed(false)
{
    setSpeed(normal_speed);
}

Ghost::~Ghost() {}

void Ghost::reset()
{
    Character::reset();
    resetMode();
    out_of_den=false;
    setNormalSpeed(75);
    setSpeed(normal_speed);
    normal_speed_changed = false;
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
        std::cout << "BLINKY"<<std::endl;
        break;
    case Ghost::Type::PINKY:
        std::cout << "PINKY"<<std::endl;
        break;
    case Ghost::Type::INKY:
        std::cout << "INKY"<<std::endl;
        break;
    case Ghost::Type::CLYDE:
        std::cout << "CLYDE"<<std::endl;
        break;
    default:
        std::cout << "ERROR printType()"<<std::endl;
        break;
    }
}



void Ghost::updateDirection() {

    if(mode_just_changed==true)
    {
        direction=getOppositeDirection(direction);
        mode_just_changed=false;
    }

    /*Ghosts use a random number generator to pick a way to turn at each intersection when frightened.
     If the tile of the chosen direction is not legal, the ghost then test the legality of the tiles in that order of direction: up, left, down, and right an choose the direction of the first legal tile found*/
    if(ghost_mode==Ghost::Mode::FRIGHTENED)
    {
        //En mode FRIGTHENED, les fantomes se déplacent aléatoirement (mais toujours avec la même seed)
        std::mt19937 gen(8888); // mersenne_twister_engine seeded with rd
        std::uniform_int_distribution<> dis(0, 2); // di

        int random=dis(gen);

        //on extrait les direction qui ne sont pas l'opposé de la direction actuelle
        std::vector<Direction> not_turnaround_directions={Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT};
        not_turnaround_directions.erase(std::remove(not_turnaround_directions.begin(), not_turnaround_directions.end(), getOppositeDirection(direction)), not_turnaround_directions.end());

        //Si la direction aléatoire est légale (pas un mur) on la choisit
        if(game_model.isTileLegal(position.getNextTile(not_turnaround_directions[random]))){

            direction=not_turnaround_directions[random];
            return;
        }
        //Si la direction aléatoire est bloqué par un mur (donc illégal) on choisit la direction légal par ordre de preference up, left, down, right (sans faire demi tour)
        else{
            for (Direction d : {Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT}) {
                if (d != getOppositeDirection(direction)) {
                    if (game_model.isTileLegal(position.getNextTile(d))) {
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

            Tile next_possible_tile=position.getNextTile(d);

            if(game_model.isTileLegal(next_possible_tile)){
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

    int nb_legal_direction=next_legal_directions.size();

    //Si le tournant n'a qu'un issue, le fantome prend la direction correspondante
    if(nb_legal_direction == 1){
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
            if(position.distanceTile(next_possible_tile, current_target_tile)<min_distance && !(forbiden_tile_down && d==Direction::DOWN) && !(forbiden_tile_up && d==Direction::UP)){
                best_directions.clear();
                best_directions.push_back(d);

                min_distance=position.distanceTile(next_possible_tile, current_target_tile);
            }
            else if(position.distanceTile(next_possible_tile, current_target_tile)==min_distance && !(forbiden_tile_down && d==Direction::DOWN) && !(forbiden_tile_up && d==Direction::UP)){
                best_directions.push_back(d);
            }
        }

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

    return;


}

void Ghost::switchModeFrightened(float time_count, float fright_time_count, bool frightened_bool)
{
    previous_ghost_mode=ghost_mode;
    ghost_mode=Ghost::Mode::FRIGHTENED;
    mode_has_changed=true;
    mode_just_changed=true;
    setNormalSpeed(50);

    return;
}

void Ghost::cancelModeFrightened(float time_count, float fright_time_count, bool frightened_bool)
{
    ghost_mode=previous_ghost_mode;
    mode_has_changed=true;
    mode_just_changed=true;
    setNormalSpeed(75);
}

void Ghost::TimeBasedModeUpdate(float time_count, float fright_time_count, bool frightened_bool)
{

    //Si pacman n'a pas mangé d'energizer, on switch les modes des fantomes en fonction du temps


    //On ne change pas le mode si il vient juste de changer
    if (mode_just_changed != true) {
        if ((std::fabs(time_count - 7.0f) < 0.001f && std::fabs(time_count - 7.0f)>0.0) ||
            (std::fabs(time_count - 34.0f) < 0.001f && std::fabs(time_count - 34.0f)>0.0)||
            (std::fabs(time_count - 59.0f) < 0.001f && std::fabs(time_count - 59.0f)>0.0)||
            (std::fabs(time_count - 84.0f) < 0.001f && std::fabs(time_count - 84.0f)>0.0)){

            ghost_mode=Ghost::Mode::CHASE;
            mode_has_changed=true;
            mode_just_changed=true;
        }
        else if  ((std::fabs(time_count - 27.0f) < 0.001f && std::fabs(time_count - 27.0f)>0.0)||
                  (std::fabs(time_count - 54.0f) < 0.001f && std::fabs(time_count - 54.0f)>0.0)||
                  (std::fabs(time_count - 79.0f) < 0.001f) && std::fabs(time_count - 79.0f)>0.0){

            ghost_mode=Ghost::Mode::SCATTER;
            mode_has_changed=true;
            mode_just_changed=true;
        }
        else {
            return;
        }

    }
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

void Ghost::setOutOfDen(bool out_of_den)
{
    this->out_of_den=out_of_den;
}

bool Ghost::isOutOfDen()
{
    return out_of_den;
}


Direction Ghost::getSpawnDirection() const
{
    return spawn_direction;
}

Position Ghost::getSpawnPosition() const
{
    return spawn_position;
}

Position Ghost::getRespawnPosition() const
{
    return respawn_position;
}

void Ghost::resetMode()
{
    ghost_mode=Ghost::Mode::SCATTER;
    previous_ghost_mode=Mode::SCATTER;
    mode_has_changed=false;
    mode_just_changed=false;
}

void Ghost::updateSpeed()
{
    bool was_in_tunnel = is_in_tunnel;

    //entrée et sortie du couloir de teleportation de gauche
    if(position.toTile()==Slowing_tile_left && direction==Direction::LEFT){
        is_in_tunnel = true;
    }
    if(position.toTile()==Slowing_tile_left && direction==Direction::RIGHT){
        is_in_tunnel = false;
        setSpeed(normal_speed);
    }

    //entrée et sortie du couloir de teleportation de droite
    if(position.toTile()==Slowing_tile_right && direction==Direction::RIGHT){
        is_in_tunnel = true;
    }
    if(position.toTile()==Slowing_tile_right && direction==Direction::LEFT){
        is_in_tunnel = false;
        setSpeed(normal_speed);
    }

    if (!was_in_tunnel && is_in_tunnel) {
        setSpeed(40);
        normal_speed_changed = false;
    }

    if (normal_speed_changed && !is_in_tunnel) {
        setSpeed(normal_speed);
        normal_speed_changed = false;
    }
}

void Ghost::die()
{
    direction=spawn_direction;
    position=respawn_position;
    out_of_den=false;
}

void Ghost::move() {

    updateSpeed();

    if (!should_move())
        return;

    updateTargetTile();


    if(out_of_den==false && monster_den.getCanLeaveDen(ghost_type)==true)
    {

        leaveTheDen();
    }

    if (frames_to_drop > 0)
        frames_to_drop--;
    else
    {
        if(position.isCenteredOnTile() && out_of_den==true){
            updateDirection();
        }

        if(monster_den.getCanLeaveDen(ghost_type)==true){
            updatePosition();
        }
    }
}

void Ghost::setNormalSpeed(int normal_speed) {
    this->normal_speed = normal_speed;
    normal_speed_changed = true;
}
