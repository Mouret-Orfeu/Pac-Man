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