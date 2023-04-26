#include "GameModel.h"

#include <iostream>

GameModel::GameModel() : count(0) {
    // Initialize other game objects here
}

GameModel::~GameModel() {
    // Clean up if necessary
}

void GameModel::update() {
    // Update Ghost position
    ghost.updatePosition(count);

    // Update other game objects here
    count = (count + 1) % 512;
}

Ghost& GameModel::getGhost() {
    return ghost;
}

int GameModel::getCount() const {
    return count;
}

void GameModel::setCount(int count) {
    this->count = count;
}
