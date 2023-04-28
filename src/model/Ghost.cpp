#include "Ghost.h"

#include "view/GameView.h"

Ghost::Ghost()
:Character({Direction::RIGHT, GameViewConstants::init_pos_center_Blinky, computeTilePosition(GameViewConstants::init_pos_center_Blinky)})
{
    // Initialize Ghost-specific data here
}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

void Ghost::move(int count) {
    // Update the direction based on the count value
    switch (count / 128) {
        case 0:
            state.direction = Direction::RIGHT;
            state.center_position.x++;
            break;
        case 1:
            state.direction = Direction::DOWN;
            state.center_position.y++;
            break;
        case 2:
            state.direction = Direction::LEFT;
            state.center_position.x--;
            break;
        case 3:
            state.direction = Direction::UP;
            state.center_position.y--;
            break;
    }
}
