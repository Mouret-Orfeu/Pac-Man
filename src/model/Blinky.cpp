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
 speed1(1),
 speed2(2),
 speed3(3),
 current_speed(speed1)
{}


Blinky::~Blinky() {
    // Clean up Blinky-specific data here
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

int Blinky::getCurrentSpeed() const
{
    return current_speed;
}

int Blinky::getSpeed1() const
{
    return speed1;
}

int Blinky::getSpeed2() const
{
    return speed2;
}

int Blinky::getSpeed3() const
{
    return speed3;
}

void Blinky::die()
{
    direction=spawn_direction;
    position=respawn_position;
    out_of_den=false;
    current_speed=speed1;
}



