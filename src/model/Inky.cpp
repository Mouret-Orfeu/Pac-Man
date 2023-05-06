#include "Inky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Inky = Position((WINDOW_WIDTH-1)/2-2*TILE_SIZE, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Inky = {WINDOW_ROWS-1,WINDOW_COLS-1};

Inky::Inky(GameModel& game_model, PacMan& pacman, std::unique_ptr<Ghost>& blinky_uniq_ptr)
:Ghost(game_model, Ghost::Type::INKY, init_pos_Inky, Direction::UP, scatter_target_tile_Inky, false,false, pacman),
blinky_uniq_ptr(blinky_uniq_ptr)
{}

Inky::~Inky() {
    // Clean up Inky-specific data here
}

Tile Inky::findChaseTargetTile()
{
    Tile Blinky_tile= blinky_uniq_ptr->getPosition().toTile();

    switch(pacman.getMemoryDirection()){
        case Direction::UP:
            return {pacman.getPosition().toTile().i-2+(pacman.getPosition().toTile().i-2-Blinky_tile.i),
                    pacman.getPosition().toTile().j+(pacman.getPosition().toTile().j-Blinky_tile.j)};
        case Direction::DOWN:
            return {pacman.getPosition().toTile().i+2+(pacman.getPosition().toTile().i+2-Blinky_tile.i),
                    pacman.getPosition().toTile().j+(pacman.getPosition().toTile().j-Blinky_tile.i)};
        case Direction::LEFT:
            return {pacman.getPosition().toTile().i+(pacman.getPosition().toTile().i-Blinky_tile.i),
                    pacman.getPosition().toTile().j-2+(pacman.getPosition().toTile().j-2-Blinky_tile.i)};
        case Direction::RIGHT:
            return {pacman.getPosition().toTile().i+(pacman.getPosition().toTile().i-Blinky_tile.i),    
                    pacman.getPosition().toTile().j-2+(pacman.getPosition().toTile().j-2-Blinky_tile.i)};
        default:
            std::cout<<"erreur dans Inky::findChaseTargetTile()"<<std::endl;
            exit(1);
    }
}

void Inky::updateTargetTile()
{
    if(ghost_mode==Ghost::Mode::CHASE){
            current_target_tile=Inky::findChaseTargetTile();
    }

    if(ghost_mode==Ghost::Mode::SCATTER){
        current_target_tile=scatter_target_tile;
    }
}

void Inky::leaveTheDen()
{
    if(position==init_pos_Inky)
    {
        direction=Direction::RIGHT;
        return;
    }
    else if(position==center_den_position)
    {
        direction=Direction::UP;
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
