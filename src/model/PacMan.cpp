#include "PacMan.h"
#include "Character.h"

#include "GameModel.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"

#include <iostream>
const Position init_pos_pacman = Position((WINDOW_WIDTH-1)/2, 26*TILE_SIZE + (TILE_SIZE-1)/2);

PacMan::PacMan(GameModel& gameModel)
:Character(gameModel, init_pos_pacman, Direction::RIGHT),
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
        eat();
        updateDirection();
    }

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    if (frames_to_drop > 0)
        frames_to_drop--;
    else
        updatePosition();
}

void PacMan::eat() {
    Tile current_tile = position.toTile();
    switch (gameModel.getTile(current_tile)) {
        case GameModel::TileType::DOT:
            gameModel.setTile(current_tile, GameModel::TileType::EMPTY);
            score+=10;
            frames_to_drop = 1;
            break;
        case GameModel::TileType::ENERGIZER:
            gameModel.setTile(current_tile, GameModel::TileType::EMPTY);
            score+=50;
            frames_to_drop = 3;
            break;
        default:
            break;
    }
    if (score > highscore)
        highscore = score;
}

void PacMan::updateDirection() {
    // Update the direction based on the intended direction
    if (intended_direction != Direction::NONE) {
        Tile next_tile_intended = position.getNextTile(intended_direction);
        if(gameModel.isTileLegal(next_tile_intended) && position.isCenteredOnTile()) {
            direction = intended_direction;
            sprite_orientation = intended_direction;
        }
    }

    Tile next_tile = position.getNextTile(direction);
    if(!gameModel.isTileLegal(next_tile) && position.isCenteredOnTile())
        direction = Direction::NONE;
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
