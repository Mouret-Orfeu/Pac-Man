#include "Pinky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Pinky = Position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Pinky = {0,2};

Pinky::Pinky(GameModel& game_model, PacMan& pacman)
:Ghost(game_model, Ghost::Type::PINKY, init_pos_Pinky, Direction::DOWN, scatter_target_tile_Pinky, false,false, pacman)
{}

Pinky::~Pinky() {
    // Clean up Pinky-specific data here
}

Tile Pinky::findChaseTargetTile()
{
    switch(pacman.getMemoryDirection()){
        case Direction::UP:
            return {pacman.getPosition().toTile().i-4,pacman.getPosition().toTile().j};
        case Direction::DOWN:
            return {pacman.getPosition().toTile().i+4,pacman.getPosition().toTile().j};
        case Direction::LEFT:
            return {pacman.getPosition().toTile().i,pacman.getPosition().toTile().j-4};
        case Direction::RIGHT:
            return {pacman.getPosition().toTile().i,pacman.getPosition().toTile().j+4};
        default:
            std::cout<<"erreur dans Pinky::findChaseTargetTile()"<<std::endl;
            exit(1);
    }
}

void Pinky::updateTargetTile()
{
    if(ghost_mode==Ghost::Mode::CHASE){
            current_target_tile=Pinky::findChaseTargetTile();
    }

    if(ghost_mode==Ghost::Mode::SCATTER){
        current_target_tile=scatter_target_tile;
    }
}

void Pinky::leaveTheDen()
{
    if(position==init_pos_Pinky)
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



