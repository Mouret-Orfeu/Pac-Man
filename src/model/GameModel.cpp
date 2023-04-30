#include "GameModel.h"
#include "Character.h"
#include "common/Direction.h"

#include "Ghost.h"
#include "Blinky.h"
// #include "Pinky.h"
// #include "Inky.h"
// #include "Clyde.h"

#include <iostream>
#include <array>
#include <memory>

GameModel::GameModel()
:count(0),
 pacman(),
 ghosts {
    std::make_unique<Blinky>(),
    // std::make_unique<Pinky>(),
    // std::make_unique<Inky>(),
    // std::make_unique<Clyde>()
 }
{
    // Initialize other game objects here
}

GameModel::~GameModel() {
    // Clean up if necessary
}

void GameModel::update(Direction input_direction) {
    // Make the ghosts move
    for (std::unique_ptr<Ghost>& ghost : ghosts)
        ghost->move(count);

    // Update PacMan's intended direction based on user input
    if (input_direction != Direction::NONE)
        pacman.setIntendedDirection(input_direction);

    // Make PacMan move
    pacman.move(count);

    // Update the count
    count = (count + 1) % 512;
}

std::array<std::unique_ptr<Ghost>, 1>& GameModel::getGhosts() {
    return ghosts;
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

