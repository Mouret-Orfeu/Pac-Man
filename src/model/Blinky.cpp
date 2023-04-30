#include "Blinky.h"

#include "common/Position.h"
#include "common/Direction.h"


Blinky::Blinky()
:Ghost(Position(Tile({4,1})), Direction::RIGHT)
{
    // Initialize Blinky-specific data here
}

Blinky::~Blinky() {
    // Clean up Blinky-specific data here
}

void Blinky::move(int count) {
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
