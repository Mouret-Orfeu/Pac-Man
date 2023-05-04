#include "Direction.h"
#include <unordered_map>

bool compareDirections( Direction& dir1, Direction& dir2){
    // Define the priority order of directions
    std::unordered_map<Direction, int> priorityMap = {
        {Direction::UP, 4},
        {Direction::LEFT, 3},
        {Direction::DOWN, 2},
        {Direction::RIGHT, 1},
        {Direction::NONE, 0}
    };
    
    // Compare the priority of the directions
    return priorityMap[dir1] > priorityMap[dir2];
}

Direction getOppositeDirection(Direction d){
    switch (d)
    {
    case Direction::UP:
        return Direction::DOWN;
    case Direction::DOWN:
        return Direction::UP;
    case Direction::LEFT:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::LEFT;
    default:
        return Direction::NONE;
    }
}