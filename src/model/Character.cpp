#include "common/Position.h"
#include "Character.h"
#include "common/Direction.h"


#include <iostream>

Character::Character(GameModel& game_model, Position spawn_position, Direction spawn_direction)
:game_model(game_model),
 spawn_position(spawn_position),
 position(spawn_position),
 direction(spawn_direction),
 spawn_direction(spawn_direction),
 frames_to_drop(0),
 TELEPORTATION_TILE_RIGHT(3+(MAZE_ROWS/2)-1, MAZE_COLS-1),
 TELEPORTATION_TILE_LEFT(3+(MAZE_ROWS/2)-1, 0)
{}

Character::~Character() {}

void Character::reset(){
    position = spawn_position;
    direction = spawn_direction;
    frames_to_drop = 0;
}


Position Character::getPosition() const {
    return position;
}

Direction Character::getDirection() const {
    return direction;
}

void Character::setDirection(Direction direction) {
    this->direction = direction;
}

void Character::updatePosition () {
    switch (direction) {
        case Direction::UP:
            position.incrementY(-1);
            break;
        case Direction::DOWN:
            position.incrementY(1);
            break;
        case Direction::LEFT:
            position.incrementX(-1);
            break;
        case Direction::RIGHT:
            position.incrementX(1);
            break;
        default:
            break;
    }
    // Make the character teleport from one side to the other
    if (position.getX() < -TILE_SIZE) {
        position.setX(WINDOW_WIDTH + TILE_SIZE - 1);
    }
    else if (position.getX() >= WINDOW_WIDTH + TILE_SIZE) {
        position.setX(-TILE_SIZE);
    }
}

void Character::printDirection(Direction d) const
{


    switch (d)
    {
    case Direction::UP:
        std::cout <<"direction: UP"<< std::endl;
        break;
    case Direction::DOWN:
        std::cout <<"direction: DOWN"<< std::endl;
        break;
    case Direction::LEFT:
        std::cout <<"direction: LEFT"<< std::endl;
        break;
    case Direction::RIGHT:
        std::cout <<"direction: RIGHT"<< std::endl;
        break;
    case Direction::NONE:
        std::cout <<"direction: NONE"<< std::endl;
        break;
    default:
        break;
    }
}

void Character::setPosition(Position position) {
    this->position = position;
}

Position Character::getSpawnPos() const {
    return spawn_position;
}

void Character::setFramesToDrop(int frames) {
    frames_to_drop = frames;
}

