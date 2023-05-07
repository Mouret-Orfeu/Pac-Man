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
#include <cmath>


GameModel::GameModel()
:count(0),
 monster_den(*this),
 pacman(*this, monster_den),
 ghosts {
    //!!Ne pas changer l'ordre de rangement des fantomes dans ghosts!! (utilisé dans MonsterDen::updateMonsterDen())
    std::make_unique<Blinky>(*this, pacman, monster_den),
    std::make_unique<Pinky>(*this, pacman, monster_den),
    std::make_unique<Inky>(*this, pacman, ghosts[0], monster_den),
    std::make_unique<Clyde>(*this, pacman, monster_den)},
    frightened_bool(false)
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

void GameModel::GhostSwitchMode(float time_count, std::array<std::unique_ptr<Ghost>, 4>& ghosts, float fright_time_count)
{
    //Activer mode frightened quand pacman mange un energizer
    if(pacman.isEnergized() && frightened_bool == false){
        //DEBUG
        std::cout<<"frightened mode ON"<<std::endl;

        frightened_bool = true;
        for (std::unique_ptr<Ghost>& ghost : ghosts) {
            ghost->setPreviousMode(ghost->getMode());
            ghost->setMode(Ghost::Mode::FRIGHTENED);
            ghost->setModeHasChanged(true);
            ghost->setModeJustChanged(true);
        }
        return;
    }

    //Desactiver mode frightened au bout de 7 secondes
    if(pacman.isEnergized() && frightened_bool == true && std::fabs(fright_time_count - 7.0f)<0.0001f){
        //DEBUG
        std::cout<<"frightened mode OFF"<<std::endl;

        pacman.setEnergized(false);
        frightened_bool = false;

        for (std::unique_ptr<Ghost>& ghost : ghosts) {
            ghost->setMode(ghost->getPreviousMode());
            ghost->setModeHasChanged(true);
            ghost->setModeJustChanged(true);
        }
        return;
    }


    //Si pacman n'a pas mangé d'energizer, on switch les modes des fantomes en fonction du temps
    for (std::unique_ptr<Ghost>& ghost : ghosts) { 

        //On ne change pas le mode si il vient juste de changer
        if (ghost->getModeJustChanged() != true) {

            if (std::fabs(time_count - 7.0f) < 0.0001f ||
                std::fabs(time_count - 34.0f) < 0.0001f ||
                std::fabs(time_count - 59.0f) < 0.0001f ||
                std::fabs(time_count - 84.0f) < 0.0001f) {
                ghost->setMode(Ghost::Mode::CHASE);
                ghost->setModeHasChanged(true);
                ghost->setModeJustChanged(true);

                //DEBUG
                //std::cout << "Chase" << std::endl;
            }
            else if  (std::fabs(time_count - 27.0f) < 0.0001f ||
                      std::fabs(time_count - 54.0f) < 0.0001f ||
                      std::fabs(time_count - 79.0f) < 0.0001f) {
                
                ghost->setMode(Ghost::Mode::SCATTER);
                ghost->setModeHasChanged(true);
                ghost->setModeJustChanged(true);

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

void GameModel::HandlePacGhostCollision()
{
    
    for(std::unique_ptr<Ghost>& ghost : ghosts){
        if(pacman.getPosition().toTile() == ghost->getPosition().toTile()){
            if(frightened_bool==false){

                pacman.setIsDead(true);
                pacman.setLives(pacman.getLives()-1);
                pacman.setDirection(Direction::RIGHT);
                pacman.setIntendedDirection(Direction::RIGHT);
                pacman.setMemoryDirection(Direction::RIGHT);
        
            }

            else if(frightened_bool==true){
                pacman.setScore(pacman.getScore()+200);
    
            }
        }
    }

   
}

void GameModel::update(Direction input_direction, float time_count, float fright_time_count) {

    HandlePacGhostCollision();

    //On libère les fantomes qui doivent l'être
    monster_den.updateMonsterDen();
    
    //En fonction du temps qui passe, on change le mode des fantomes
    GhostSwitchMode(time_count, ghosts, fright_time_count);

    //DEBUG
    //test de FRIGHTENED (faut commenter GhostSwitchMode au dessus pour ce test)
    //if(std::fabs(time_count - 7.0f) < 0.0001f && frightened_bool == false){
    //    for(std::unique_ptr<Ghost>& ghost : ghosts){
    //        frightened_bool = true;
    //        ghost->setPreviousMode(ghost->getMode());
    //        ghost->setMode(Ghost::Mode::FRIGHTENED);
    //        ghost->setModeHasChanged(true);
    //        ghost->setModeJustChanged(true);
    //    }
//
    //    //DEBUG
    //    //std::cout<<"frighten change"<<std::endl;
    //}

    
    // Make the ghosts move
    for (std::unique_ptr<Ghost>& ghost : ghosts){
        //DEBUG
        //std::cout<<"boucle ghost"<<std::endl;

        //DEBUG
        //ghost->printType(ghost->getType());

        ghost->move(count);

        //DEBUG
        //std::cout<<"après move "<<std::endl;
    }


    // Update PacMan's intended direction based on user input
    if (input_direction != Direction::NONE)
        pacman.setIntendedDirection(input_direction);

    // Make PacMan move
    pacman.move(count);

    


    // Update the count, (je pense que ça sert plus à rien ça)
    count = (count + 1) % 512;

    //DEBUG
    //monster_den.printCounterDot(Ghost::Type::INKY);
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

bool GameModel::getFrightenedBool() const
{
    return frightened_bool;
}

void GameModel::setLastTimeDotEatenTimer(float time)
{
    last_time_dot_eaten_timer = time;
}

float GameModel::getLastTimeDotEatenTimer() const
{
    return last_time_dot_eaten_timer;
}

