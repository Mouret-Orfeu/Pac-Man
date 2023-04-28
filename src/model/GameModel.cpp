#include "GameModel.h"
#include "Character.h"

#include <iostream>

GameModel::GameModel()
:count(0),
 blinky(),
 pacman()
{
    // Initialize other game objects here
}

GameModel::~GameModel() {
    // Clean up if necessary
}

void GameModel::update(Character::Direction input_direction) {
    // Update Ghost top_left_position
    blinky.move(count);

    // Update PacMan top_left_position
    if (input_direction != Character::Direction::NONE)
        pacman.setIntendedDirection(input_direction);
    pacman.move(count);

    // Update other game objects here
    count = (count + 1) % 512;
}

Ghost& GameModel::getGhost() {
    return blinky;
}

PacMan& GameModel::getPacMan() {
    return pacman;
}

int GameModel::getCount() const {
    return count;
}

void GameModel::setCount(int count) {
    this->count = count;
}

int GameModel::getScore() const {
    return score;
}

void GameModel::setScore(int score) {
    this->score = score;
}

int GameModel::getHighScore() const {
    return highscore;
}

void GameModel::setHighScore(int highscore) {
    this->highscore = highscore;
}

int GameModel::getLives() const {
    return lives;
}

void GameModel::setLives(int lives) {
    this->lives = lives;
}

bool GameModel::getDeath() const {
    return death;
}

void GameModel::setDeath(bool death) {
    this->death = death;
}

