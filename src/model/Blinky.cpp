#include "Blinky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "common/Tile.h"
#include "GameModel.h"
#include "Ghost.h"

#include <vector>
#include <iostream>
#include <algorithm>

const Position spawn_pos_Blinky = Position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2);
const Position respawn_pos_Blinky = Position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Blinky = {0,WINDOW_COLS-3};

Blinky::Blinky(GameModel& game_model, PacMan& pacman, MonsterDen& monster_den)
:Ghost(game_model, Ghost::Type::BLINKY, spawn_pos_Blinky,respawn_pos_Blinky, Direction::LEFT, scatter_target_tile_Blinky, true, pacman, monster_den),
 speed1(75),
 speed2(80),
 speed3(90)
{
    setSpeed(speed1);
}


Blinky::~Blinky() {}

void Blinky::reset()
{
    Ghost::reset();
    setSpeed(speed1);
}

void Blinky::leaveTheDen()
{
    if(position==center_den_position)
    {
        direction=Direction::UP;
        return;
    }
    else if(position==out_of_den_position)
    {
        direction=Direction::LEFT;
        out_of_den=true;
    }
    else{
        ;
    }
}

void Blinky::updateTargetTile()
{
    if(ghost_mode==Ghost::Mode::CHASE){
        current_target_tile=pacman.getPosition().toTile();
    }

    if(ghost_mode==Ghost::Mode::SCATTER){
        current_target_tile=scatter_target_tile;
    }
}

void Blinky::updateSpeed()
{
    //entrée et sortie du couloir de teleportation de gauche
    if(position.toTile()==Slowing_tile_left && direction==Direction::LEFT){
        setSpeed(40);
    }
    if(position.toTile()==Slowing_tile_left && direction==Direction::RIGHT){
        setSpeed(normal_speed);
    }

    //entrée et sortie du couloir de teleportation de droite
    if(position.toTile()==Slowing_tile_right && direction==Direction::RIGHT){
        setSpeed(40);
    }
    if(position.toTile()==Slowing_tile_right && direction==Direction::LEFT){
        setSpeed(normal_speed);
    }

    //Quand clyde sort du den, Blinky passe en vitesse 2 s'il ne l'est pas déjà
    if(monster_den.getCanLeaveDen(Type::CLYDE)==true && normal_speed==speed1){
        normal_speed=speed2;
        setSpeed(speed2);
    }

    //acceleration basé sur le nombre de dot restant
    if(pacman.getDotsEaten()==game_model.getNbDotTotal()-20 && normal_speed!=speed2){
        normal_speed=speed2;
        setSpeed(speed2);
    }
    if(pacman.getDotsEaten()==game_model.getNbDotTotal()-10 && normal_speed!=speed3){
        normal_speed=speed3;
        setSpeed(speed3);
    }
}


void Blinky::TimeBasedModeUpdate(float time_count, float fright_time_count, bool frightened_bool)
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

            if(normal_speed==speed1){
                ghost_mode=Ghost::Mode::SCATTER;
                mode_has_changed=true;
                mode_just_changed=true;
            }
            //Si blinky est en mode elroy (normal_speed!=speed1, il ne passe plus en mode scatter)
            else{
                ghost_mode=Ghost::Mode::CHASE;
            }
        }
        else {
            return;
        }

    }
}

void Blinky::die()
{
    direction=spawn_direction;
    position=respawn_position;
    out_of_den=false;
    normal_speed=speed1;
}
