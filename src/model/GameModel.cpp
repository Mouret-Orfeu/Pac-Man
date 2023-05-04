#include "GameModel.h"
#include "common/Direction.h"

#include "Character.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

#include <iostream>
#include <array>
#include <memory>


GameModel::GameModel()
:count(0),
 pacman(*this),
 ghosts {
    std::make_unique<Blinky>(*this, pacman),
    std::make_unique<Pinky>(*this, pacman),
    std::make_unique<Inky>(*this, pacman, ghosts[0]),
    std::make_unique<Clyde>(*this, pacman)

}
{
    //DEBUG
    //std::cout<<"pinky type: "<<(int)ghosts[1]->getType()<<std::endl;

    // Copy the initial matrix to the editable matrix
    for (int i = 0; i < WINDOW_ROWS; ++i) {
        for (int j = 0; j < WINDOW_COLS; ++j) {
            tilesMatrix[i][j] = INITIAL_TILES_MATRIX[i][j];
        }
    }
}

GameModel::~GameModel() {
    // Clean up if necessary
}

void GameModel::GhostSwitchMode(int second_count, std::array<std::unique_ptr<Ghost>, 4>& ghosts)
{
    for (std::unique_ptr<Ghost>& ghost : ghosts) {
        switch(second_count){
            case 7:
                ghost->setMode(Ghost::Mode::CHASE);
                break;
            case 27:
                ghost->setMode(Ghost::Mode::SCATTER);
                break;
            case 34:
                ghost->setMode(Ghost::Mode::CHASE);
                break;
            case 54:
                ghost->setMode(Ghost::Mode::SCATTER);
                break;
            case 59:
                ghost->setMode(Ghost::Mode::CHASE);
                break;
            case 79:
                ghost->setMode(Ghost::Mode::SCATTER);
                break;
            case 84:
                ghost->setMode(Ghost::Mode::CHASE);
                break;
            default:
                break;
        }
    }
}

void GameModel::update(Direction input_direction, int second_count) {
    
    //En fonction du temps qui passe, on change le mode des fantomes
    GhostSwitchMode(second_count, ghosts);
    
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

std::array<std::unique_ptr<Ghost>, 4>& GameModel::getGhosts() {
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

GameModel::TileType GameModel::getTile(Tile tile) const {
    return tilesMatrix[tile.i][tile.j];
}

void GameModel::setTile(Tile tile, TileType value) {
    tilesMatrix[tile.i][tile.j] = value;
}

bool GameModel::isTileLegal(Tile tile) {
    return getTile(tile) != GameModel::TileType::WALL;
}
