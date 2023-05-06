#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <iostream>

Character::Character(GameModel& gameModel, Position initial_position, Direction direction, Direction sprite_orientation)
:gameModel(gameModel),
 initial_position(initial_position),
 position(initial_position),
 direction(direction),
 sprite_orientation(sprite_orientation),
 frames_to_drop(0)
{}

Character::Character(GameModel& gameModel, Position position, Direction direction)
:Character(gameModel, position, direction, direction)
{}

Character::~Character() {}


Position Character::getPosition() const {
    return position;
}

Direction Character::getDirection() const {
    return direction;
}

void Character::setDirection(Direction direction) {
    this->direction = direction;
}

Direction Character::getSpriteOrientation() const {
    return sprite_orientation;
}

void Character::setSpriteOrientation(Direction sprite_orientation) {
    this->sprite_orientation = sprite_orientation;
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

Tile Character::getTeleportationTileRight() const
{
    return TELEPORTATION_TILE_RIGHT;
}

Tile Character::getTeleportationTileLeft() const
{
    return TELEPORTATION_TILE_LEFT;
}

void Character::printDirection() const
{


    switch (direction)
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

