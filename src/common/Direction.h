#pragma once

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

/**
* @brief Definit un ordre de priorité entre les directions
*/
bool compareDirections( Direction& dir1, Direction& dir2);


