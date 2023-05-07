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
    frightened_bool(false),
    nb_point_eat_ghost(200)
{
    //DEBUG
    //std::cout<<"pinky type: "<<(int)ghosts[1]->getType()<<std::endl;
    resetTilesMatrix();

}

GameModel::~GameModel() {
    // Clean up if necessary
}

void GameModel::resetTilesMatrix()
{
    // Copy the initial matrix to the editable matrix
    for (int i = 0; i < WINDOW_ROWS; ++i) {
        for (int j = 0; j < WINDOW_COLS; ++j) {
            tilesMatrix[i][j] = INITIAL_TILES_MATRIX[i][j];
        }
    }
}

void GameModel::GhostSwitchMode(float time_count, std::array<std::unique_ptr<Ghost>, 4>& ghosts, float fright_time_count)
{
    if(pacman.isEnergized() && frightened_bool == false){
        //DEBUG
        //std::cout<<"frightened mode ON"<<std::endl;

        frightened_bool = true;
        frightened_counter = 0;
        for (std::unique_ptr<Ghost>& ghost : ghosts) {
            ghost->switchModeFrightened(time_count, fright_time_count, frightened_bool);
        }
    }
    else if(pacman.isEnergized() && frightened_bool == true && std::fabs(fright_time_count - 7.0f)<0.0001f){
        //DEBUG
        //std::cout<<"frightened mode OFF"<<std::endl;

        pacman.setEnergized(false);
        frightened_bool = false;
        nb_point_eat_ghost = 200;

        for (std::unique_ptr<Ghost>& ghost : ghosts) {
            ghost->cancelModeFrightened(time_count, fright_time_count, frightened_bool);
        }
    
    }
    else{
        for (std::unique_ptr<Ghost>& ghost : ghosts) {
            ghost->TimeBasedModeUpdate(time_count, fright_time_count, frightened_bool);
        }
    }

    if (pacman.isEnergized() && frightened_bool == true) {
        frightened_counter++;
    }
}


void GameModel::HandlePacGhostCollision()
{
    bool ghost_die=false;

    for(std::unique_ptr<Ghost>& ghost : ghosts){
        if(pacman.getPosition().distancePosition(ghost->getPosition())<TILE_SIZE){
            if(frightened_bool==false){

                //DEBUG
                //std::cout<<"pacman before dead"<<std::endl;
                pacman.die();

                //tous les fantomes reviennent à leur spawn_position
                for(std::unique_ptr<Ghost>& ghost : ghosts){
                    ghost->setPosition(ghost->getSpawnPosition());
                    ghost->setDirection(ghost->getSpawnDirection());
                    if(ghost->getType()!=Ghost::Type::BLINKY){
                        ghost->setOutOfDen(false);
                    }
                }

                //DEBUG
                //std::cout<<"pacman after dead"<<std::endl;
            }
            else if(frightened_bool==true){
                pacman.setScore(pacman.getScore()+nb_point_eat_ghost);
                nb_point_eat_ghost*=2;
                pacman.setFramesToDrop(60);
                ghost->die();

                ghost_die=true;
            }
        }
    }

    for(std::unique_ptr<Ghost>& ghost : ghosts){

        if(ghost_die==true){
            ghost->setFramesToDrop(60);
        }
    }


}

void GameModel::update(Direction input_direction, float time_count, float fright_time_count) {

    if(pacman.getDotsEaten()== 244 || pacman.getLives()==-1){
        game_reset();
    }


    HandlePacGhostCollision();



    //On libère les fantomes qui doivent l'être
    monster_den.updateMonsterDen();


    //En fonction du temps qui passe, on change le mode des fantomes
    GhostSwitchMode(time_count, ghosts, fright_time_count);



    // Make the ghosts move
    for (std::unique_ptr<Ghost>& ghost : ghosts){


        ghost->move(count);
    }


    // Update PacMan's intended direction based on user input
    if (input_direction != Direction::NONE)
        pacman.setIntendedDirection(input_direction);

    // Make PacMan move
    pacman.move(count);

    // Update the count, (je pense que ça sert plus à rien ça)
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
    if ((tile.j < 0 || tile.j >= WINDOW_COLS)) {
        if (tile.i == 17)
            return GameModel::TileType::EMPTY;
        else
            return GameModel::TileType::WALL;
    }


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

Uint64 GameModel::getFrightenedCounter() const
{
    return frightened_counter;
}

void GameModel::setLastTimeDotEatenTimer(float time)
{
    last_time_dot_eaten_timer = time;
}

float GameModel::getLastTimeDotEatenTimer() const
{
    return last_time_dot_eaten_timer;
}

void GameModel::game_reset()
{
    //Ghosts
    for(std::unique_ptr<Ghost>& ghost : ghosts){
        ghost->reset();
    }

    //Pacman
    pacman.reset();

    //MonsterDen
    monster_den.reset();

    //GameModel:
    frightened_bool = false;
    last_time_dot_eaten_timer=0.0f;
    nb_point_eat_ghost=200;

    //TilesMatrix
    resetTilesMatrix();
}

