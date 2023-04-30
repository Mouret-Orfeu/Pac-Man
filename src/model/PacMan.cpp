#include "PacMan.h"
#include "Character.h"

#include "GameModel.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"

#include <iostream>


PacMan::PacMan(GameModel& gameModel)
:Character(gameModel, Position((WINDOW_WIDTH-1)/2, 26*TILE_SIZE + (TILE_SIZE-1)/2), Direction::RIGHT),
 intended_direction(Direction::RIGHT),
 score(0),
 highscore(0),
 lives(3),
 is_dead(false)
{}

PacMan::~PacMan() {}

// Implement PacMan-specific methods here
void PacMan::move(int count) {
    (void)count;

    // Eat dots and power pellets
    if (position.isCenteredOnTile()) {
        Tile current_tile = position.toTile();
        switch (gameModel.getTile(current_tile)) {
            case GameModel::TileType::DOT:
                gameModel.setTile(current_tile, GameModel::TileType::EMPTY);
                score+=10;
                break;
            case GameModel::TileType::ENERGIZER:
                gameModel.setTile(current_tile, GameModel::TileType::EMPTY);
                score+=50;
                break;
            default:
                break;
        }
        if (score > highscore)
            highscore = score;
    }

    // DEBUG: Print the current position
    // std::cout << "position.toTile(): (" << position.toTile().i << ", " << position.toTile().j << ")" << std::endl;
    // std::cout << "position.toTile(): " << static_cast<int>(gameModel.tilesMatrix[position.toTile().i][position.toTile().j]) << std::endl;

    // Update the direction based on the intended direction
    if (intended_direction != Direction::NONE) {
        Tile next_tile_intended = position.getNextTile(intended_direction);
        // DEBUG: Print the next tile intended
        // std::cout << "next_tile_intended: (" << next_tile_intended.i << ", " << next_tile_intended.j << ")" << std::endl;
        // std::cout << "next_tile_intended: " << static_cast<int>(gameModel.getTile(next_tile_intended) << std::endl;
        if(gameModel.isTileLegal(next_tile_intended) && (position.isCenteredOnTile() || position==initial_position)) {
            direction = intended_direction;
            sprite_orientation = intended_direction;

            // DEBUG: Print what's happening
            // std::cout << "direction = intended_direction" << std::endl;
            // std::cout << "sprite_orientation = intended_direction" << std::endl;
        } else {
            // DEBUG: Print what's happening
            // std::cout << "'if' not entered -> tile direction and sprite_orientation not updated!" << std::endl;
        }

    }

    // DEBUG: Print the intended direction
    // switch (intended_direction) {
    //     case Direction::UP:
    //         std::cout << "intended_direction: UP" << std::endl;
    //         break;
    //     case Direction::DOWN:
    //         std::cout << "intended_direction: DOWN" << std::endl;
    //         break;
    //     case Direction::LEFT:
    //         std::cout << "intended_direction: LEFT" << std::endl;
    //         break;
    //     case Direction::RIGHT:
    //         std::cout << "intended_direction: RIGHT" << std::endl;
    //         break;
    //     case Direction::NONE:
    //         std::cout << "intended_direction: NONE" << std::endl;
    //         break;
    //     default:
    //         std::cout << "intended_direction: ERROR" << std::endl;
    //         break;
    // }

    // DEBUG: Print the direction
    // switch (direction) {
    //     case Direction::UP:
    //         std::cout << "direction: UP" << std::endl;
    //         break;
    //     case Direction::DOWN:
    //         std::cout << "direction: DOWN" << std::endl;
    //         break;
    //     case Direction::LEFT:
    //         std::cout << "direction: LEFT" << std::endl;
    //         break;
    //     case Direction::RIGHT:
    //         std::cout << "direction: RIGHT" << std::endl;
    //         break;
    //     case Direction::NONE:
    //         std::cout << "direction: NONE" << std::endl;
    //         break;
    //     default:
    //         std::cout << "direction: ERROR" << std::endl;
    //         break;
    // }

    // DEBUG: Print the sprite orientation
    // switch (sprite_orientation) {
    //     case Direction::UP:
    //         std::cout << "sprite_orientation: UP" << std::endl;
    //         break;
    //     case Direction::DOWN:
    //         std::cout << "sprite_orientation: DOWN" << std::endl;
    //         break;
    //     case Direction::LEFT:
    //         std::cout << "sprite_orientation: LEFT" << std::endl;
    //         break;
    //     case Direction::RIGHT:
    //         std::cout << "sprite_orientation: RIGHT" << std::endl;
    //         break;
    //     case Direction::NONE:
    //         std::cout << "sprite_orientation: NONE" << std::endl;
    //         break;
    //     default:
    //         std::cout << "sprite_orientation: ERROR" << std::endl;
    //         break;
    // }

    Tile next_tile = position.getNextTile(direction);
    if(!gameModel.isTileLegal(next_tile) && position.isCenteredOnTile())
        direction = Direction::NONE;

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    updatePosition();
}

Direction PacMan::getIntendedDirection() const {
    return intended_direction;
}

void PacMan::setIntendedDirection(Direction direction) {
    // Update the direction
    intended_direction = direction;
}

int PacMan::getScore() const {
    return score;
}

void PacMan::setScore(int score) {
    this->score = score;
}

int PacMan::getHighScore() const {
    return highscore;
}

void PacMan::setHighScore(int highscore) {
    this->highscore = highscore;
}

int PacMan::getLives() const {
    return lives;
}

void PacMan::setLives(int lives) {
    this->lives = lives;
}

bool PacMan::isDead() const {
    return is_dead;
}

void PacMan::setIsDead(bool is_dead) {
    this->is_dead = is_dead;
}
