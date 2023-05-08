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
:frame_count(0),
 monster_den(*this),
 pacman(*this, monster_den),
 ghosts {
    //!!Ne pas changer l'ordre de rangement des fantomes dans ghosts!! (utilisé dans MonsterDen::updateMonsterDen())
    std::make_unique<Blinky>(*this, pacman, monster_den),
    std::make_unique<Pinky>(*this, pacman, monster_den),
    std::make_unique<Inky>(*this, pacman, ghosts[0], monster_den),
    std::make_unique<Clyde>(*this, pacman, monster_den)},
    frightened_bool(false),
    nb_point_eat_ghost(200),
    time_count(0.0f),
    fright_time_count(0.0f),
    NB_DOT_TOTAL(244),
    fruit(false),
    frame_fruit(0),
    fruit_position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2+3*TILE_SIZE),
    start_state(true),
    game_over_state(false)
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

void GameModel::updateGhostMode()
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
        //pacman.setSpeed(80);
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

    if(!getFrightenedBool())
        setTimeCount(getTimeCount()+ 1.0f/60.0f) ;
    else
        setFrightTimeCount(getFrightTimeCount()+ 1.0f/60.0f) ;

    if(getFrightTimeCount() > 7.1f)

        setFrightTimeCount(0.0f);

    //DEBUG
    //std::cout << "time_count: " << getTimeCount() << std::endl;

    //DEBUG
    //it++;
    //if(it%60==0){
    //    std::cout << "Second fright: " << static_cast<int>(fright_time_count) << std::endl;
    //    it=0;
    //}


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

                time_count=0.0f;

                //tous les fantomes reviennent à leur spawn_position, et leur mode de départ
                for(std::unique_ptr<Ghost>& ghost : ghosts){
                    ghost->setPosition(ghost->getSpawnPosition());
                    ghost->setDirection(ghost->getSpawnDirection());
                    if(ghost->getType()!=Ghost::Type::BLINKY){
                        ghost->setOutOfDen(false);
                    }
                    ghost->resetMode();

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

void GameModel::update(Direction input_direction) {

    //Traitement du cas où pacman a mangé toutes les gommes ou a perdu toutes ses vies
    if(pacman.getDotsEaten()== 244 || pacman.getLives()==-1){
        reset();
    }


    //On libère les fantomes qui doivent l'être
    monster_den.updateMonsterDen();

    //En fonction du temps qui passe, on change le mode des fantomes
    updateGhostMode();

    // Make the ghosts move
    for (std::unique_ptr<Ghost>& ghost : ghosts){
        ghost->move();
    }

    // Update PacMan's intended direction based on user input
    if (input_direction != Direction::NONE)
        pacman.setIntendedDirection(input_direction);

    // Make PacMan move
    pacman.move();

    HandlePacGhostCollision();

    upDateFruit();

    // Update the frame_count, (je pense que ça sert plus à rien ça)
    frame_count++;
}

std::array<std::unique_ptr<Ghost>, 4>& GameModel::getGhosts() {
    return ghosts;
}

PacMan& GameModel::getPacMan() {
    return pacman;
}

int GameModel::getFrameCount() const {
    return frame_count;
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

void GameModel::reset()
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
    last_time_dot_eaten_timer = 0.0f;
    nb_point_eat_ghost = 200;
    time_count = 0.0f;
    fright_time_count = 0.0f;
    frame_count = 0;
    fruit= false;
    frame_fruit= 0;
    start_state=false;
    game_over_state=false;


    //TilesMatrix
    resetTilesMatrix();
}

void GameModel::setTimeCount(float time_count)
{
    this->time_count = time_count;
}

float GameModel::getTimeCount() const
{
    return time_count;
}

void GameModel::setFrightTimeCount(float fright_time_count)
{
    this->fright_time_count = fright_time_count;
}

float GameModel::getFrightTimeCount() const
{
    return fright_time_count;
}

void GameModel::setFrightenedCounter(Uint64 frightened_counter)
{
    this->frightened_counter = frightened_counter;
}

int GameModel::getNbDotTotal() const
{
    return NB_DOT_TOTAL;
}

bool GameModel::getFruit() const 
{
    return fruit;
}

void GameModel::setFruit(bool fruit)
{
    this->fruit = fruit;
}

void GameModel::upDateFruit()
{
    if(fruit){
        frame_fruit++;
    }
    
    if(pacman.getDotsEaten() == 70 || pacman.getDotsEaten() == 170){
        fruit = true;
    }

    if(fruit && frame_fruit == 600){
        fruit = false;
        frame_fruit = 0;
    }

    //DEBUG
    //if(fruit)
    //    std::cout<<"fruit timer: "<<frame_fruit/60<<std::endl;
    //else
    //    std::cout<<"dot count: "<<pacman.getDotsEaten()<<std::endl;
    
}


Position GameModel::getFruitPosition() const
{
    return fruit_position;
}

void GameModel::setFrameFruit(int frame_fruit)
{
    this->frame_fruit = frame_fruit;
}

bool GameModel::getStartState() const
{
    return start_state;
}

void GameModel::setStartState(bool start_state)
{
    this->start_state = start_state;
}

bool GameModel::getGameOverState() const
{
    return game_over_state;
}

void GameModel::setGameOverState(bool game_over_state)
{
    this->game_over_state = game_over_state;
}

