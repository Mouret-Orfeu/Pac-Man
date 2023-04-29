#include "Ghost.h"
#include "GameModel.h"
#include "common/Position.h"
#include "common/Direction.h"

Ghost::Ghost()
:Character(Position(Tile({4,1})), Direction::RIGHT)
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
            direction = Direction::RIGHT;
            sprite_orientation = Direction::RIGHT;
            position.incrementX(1);
            break;
        case 1:
            direction = Direction::DOWN;
            sprite_orientation = Direction::DOWN;
            position.incrementY(1);
            break;
        case 2:
            direction = Direction::LEFT;
            sprite_orientation = Direction::LEFT;
            position.incrementX(-1);
            break;
        case 3:
            direction = Direction::UP;
            sprite_orientation = Direction::UP;
            position.incrementY(-1);
            break;
    }
}
