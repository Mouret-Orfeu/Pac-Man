#include "Pinky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Pinky = Position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Pinky = {0,2};

Pinky::Pinky(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::PINKY, init_pos_Pinky, Direction::DOWN, scatter_target_tile_Pinky, false)
{}

Pinky::~Pinky() {
    // Clean up Pinky-specific data here
}

void Pinky::move(int count) {
    (void)count;

    if(position.isCenteredOnTile() || out_of_den==false){
        //DEBUG
        //printDirection(direction);
        
        updateDirection();
    }

    //printDirection(direction);
    updatePosition();
}


void Pinky::updateDirection()
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
