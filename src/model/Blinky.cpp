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

Blinky::Blinky(GameModel& gameModel, PacMan& pacman)
:Ghost(gameModel, Ghost::Type::BLINKY, init_pos_Blinky, Direction::LEFT, scatter_target_tile_Blinky, true, pacman),
 vitesse1(1),
 vitesse2(2),
 vitesse3(3),
 respawn_position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2)
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



void Blinky::move(int count) {
    (void)count;

    updateTargetTile();

    if(out_of_den==false)
    {
        leaveTheDen();
    }

    if(position.isCenteredOnTile()){
        //DEBUG
        //printDirection(direction);
        
        updateDirection();
    }

    //printDirection(direction);
    updatePosition();
}
