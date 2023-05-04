#include "Inky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Inky = Position((WINDOW_WIDTH-1)/2-2*TILE_SIZE, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Inky = {WINDOW_ROWS-1,WINDOW_COLS-1};

Inky::Inky(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::INKY, init_pos_Inky, Direction::UP, scatter_target_tile_Inky, false)
{}

Inky::~Inky() {
    // Clean up Inky-specific data here
}

void Inky::move(int count) {
    (void)count;

    if(position.isCenteredOnTile() || out_of_den==false){
        //DEBUG
        //printDirection(direction);
        
        updateDirection();
    }

    //printDirection(direction);
    updatePosition();
}

void Inky::updateDirection()
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
