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

void GameModel::GhostSwitchMode(float time_count, std::array<std::unique_ptr<Ghost>, 4>& ghosts)
{
    for (std::unique_ptr<Ghost>& ghost : ghosts) { 

        //On ne change pas le mode si il vient juste de changer
        if (ghost->getModJustChanged() != true) {
            if (std::fabs(time_count - 7.0f) < 0.0001f ||
                std::fabs(time_count - 34.0f) < 0.0001f ||
                std::fabs(time_count - 59.0f) < 0.0001f ||
                std::fabs(time_count - 84.0f) < 0.0001f) {
                ghost->setMod(Ghost::Mode::CHASE);
                ghost->setModHasChanged(true);
                ghost->setModJustChanged(true);

                //DEBUG
                std::cout << "Chase" << std::endl;
            }
            else if  (std::fabs(time_count - 27.0f) < 0.0001f ||
                      std::fabs(time_count - 54.0f) < 0.0001f ||
                      std::fabs(time_count - 79.0f) < 0.0001f) {
                
                ghost->setMod(Ghost::Mode::SCATTER);
                ghost->setModHasChanged(true);
                ghost->setModJustChanged(true);

                //DEBUG
                //std::cout << "Scatter" << std::endl;
            }
            else {
                //DEBUG
                //std::cout << "pas de switch" << std::endl;
                return;
            }

            //DEBUG
            //if(ghost->getModJustChanged() == true){
            //    ghost->printType(ghost->getType());
            //    std::cout<<"mod just changed"<<std::endl;
            //}

        }   
            
                 
    }

    
}

void GameModel::update(Direction input_direction, float time_count) {
    
    //En fonction du temps qui passe, on change le mode des fantomes
    GhostSwitchMode(time_count, ghosts);
    
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
