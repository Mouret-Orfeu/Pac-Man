#include "PacMan.h"
#include "Character.h"

#include "GameModel.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"
#include "MonsterDen.h"

#include <iostream>

const Position spawn_pos_pacman=Position((WINDOW_WIDTH-1)/2, 26*TILE_SIZE + (TILE_SIZE-1)/2);

PacMan::PacMan(GameModel& gameModel, MonsterDen& monster_den)
:Character(gameModel, spawn_pos_pacman, Direction::RIGHT),
 monster_den(monster_den),
 intended_direction(Direction::RIGHT),
 score(0),
 highscore(0),
 lives(2),
 game_over(false),
 cornering_direction(Cornering::NONE),
 cornering(false),
 is_center_passed(Center_passed::NOT_PASSED),
 dots_eaten(0),
 memory_direction(Direction::RIGHT),
 energized(false)
{
    setSpeed(80);
}

PacMan::~PacMan() {}

void PacMan::reset()
{
    Character::reset();
    intended_direction=Direction::RIGHT;

    //si pacman n'a pas -1 vie, on continue d'enchainer les parties en accumulant le score
    if(lives==-1)
        score=0;

    lives=3;
    game_over=false;
    cornering_direction=Cornering::NONE;
    cornering=false;
    is_center_passed=Center_passed::NOT_PASSED;
    dots_eaten=0;
    memory_direction=Direction::RIGHT;
    energized=false;
}



// Implement PacMan-specific methods here
void PacMan::move() {
    if (!should_move())
        return;

    // WARNNING: we check too many things at each frame, this is not efficient

    // Eat dots and energizers
    eat();


    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    if (frames_to_drop > 0)
        frames_to_drop--;
    else {
        if (position.isCenteredHorizontallyOnTile() || position.isCenteredVerticallyOnTile())
            updateDirection();

        updatePosition();

    }
}

void PacMan::eat() {


    Tile current_tile = position.toTile();


    switch (game_model.getTile(current_tile)) {
        case GameModel::TileType::DOT:


            game_model.setTile(current_tile, GameModel::TileType::EMPTY);
            score+=10;
            frames_to_drop = 1;
            dots_eaten++;
            monster_den.incrementDotCounter();
            game_model.setLastTimeDotEatenTimer(0.0f);

            break;
        case GameModel::TileType::ENERGIZER:

            game_model.setTile(current_tile, GameModel::TileType::EMPTY);
            score+=50;
            frames_to_drop = 3;
            dots_eaten++;
            energized = true;
            setSpeed(90);
            game_model.setLastTimeDotEatenTimer(0.0f);
            game_model.setFrightTimeCount(0.0f);
            game_model.setFrightenedCounter(0);
            break;
        default:
            break;
    }

    //manger le fruit si necessaire
    if(game_model.getFruit()){

        if(position.distancePosition(game_model.getFruitPosition())==0){
            game_model.setFruit(false);
            score+=100;
        }
    }

    if (score > highscore)
        highscore = score;
}

void PacMan::setCornering()
{
    switch(direction)
    {
        case Direction::UP:
            switch(intended_direction)
            {
                case Direction::LEFT:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::DOWN_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::UP_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                case Direction::RIGHT:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::DOWN_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::UP_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case Direction::DOWN:
            switch(intended_direction)
            {
                case Direction::LEFT:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::UP_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::DOWN_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                case Direction::RIGHT:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::UP_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::DOWN_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case Direction::LEFT:
            switch(intended_direction)
            {
                case Direction::UP:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::UP_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::UP_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                case Direction::DOWN:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::DOWN_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::DOWN_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case Direction::RIGHT:
            switch(intended_direction)
            {
                case Direction::UP:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::UP_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::UP_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                case Direction::DOWN:
                    switch(is_center_passed)
                    {
                        case Center_passed::PASSED:
                            cornering_direction= Cornering::DOWN_LEFT;
                            cornering=true;
                            break;
                        case Center_passed::NOT_PASSED:
                            cornering_direction= Cornering::DOWN_RIGHT;
                            cornering=true;
                            break;
                        case Center_passed::ON_CENTER:
                            cornering_direction= Cornering::NONE;
                            cornering=false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

}

void PacMan::setIsCenterPassed()
{
    switch (direction)
    {
    case Direction::UP:
        if(position.getY()<position.getTileCenter().y)
            is_center_passed=Center_passed::PASSED;
        else if(position.getY()==position.getTileCenter().y)
            is_center_passed=Center_passed::ON_CENTER;
        else if(position.getY()>position.getTileCenter().y)
            is_center_passed=Center_passed::NOT_PASSED;
        break;
    case Direction::DOWN:
        if(position.getY()>position.getTileCenter().y)
            is_center_passed=Center_passed::PASSED;
        if(position.getY()==position.getTileCenter().y)
            is_center_passed=Center_passed::ON_CENTER;
        if(position.getY()<position.getTileCenter().y)
            is_center_passed=Center_passed::NOT_PASSED;
        break;
    case Direction::LEFT:
        if(position.getX()<position.getTileCenter().x)
            is_center_passed=Center_passed::PASSED;
        if(position.getX()==position.getTileCenter().x)
            is_center_passed=Center_passed::ON_CENTER;
        if(position.getX()>position.getTileCenter().x)
            is_center_passed=Center_passed::NOT_PASSED;
        break;
    case Direction::RIGHT:
        if(position.getX()>position.getTileCenter().x)
            is_center_passed=Center_passed::PASSED;
        if(position.getX()==position.getTileCenter().x)
            is_center_passed=Center_passed::ON_CENTER;
        if(position.getX()<position.getTileCenter().x)
            is_center_passed=Center_passed::NOT_PASSED;
        break;
    default:
        break;
    }
}

bool PacMan::turnaround() const
{
    return (direction==Direction::UP && intended_direction==Direction::DOWN)
        || (direction==Direction::DOWN && intended_direction==Direction::UP)
        || (direction==Direction::LEFT && intended_direction==Direction::RIGHT)
        || (direction==Direction::RIGHT && intended_direction==Direction::LEFT);
}

void PacMan::updateDirection() {
    //cornering va être égale à true pendant le mouvement diagonal et jusqu'au prochain centre de tile
    if(position.isCenteredOnTile()){
        cornering=false;
    }
    //cornering_direction va être égal à NONE tout le temps sauf durant le mouvement diagonal
    if(position.isCenteredHorizontallyOnTile() || position.isCenteredVerticallyOnTile()){
        cornering_direction=Cornering::NONE;
    }
    //Si PacMan veut tourner dans une nouvelle direction:
    //Update the direction based on the intended direction
    //Update le cornering
    if (intended_direction != Direction::NONE) {
        Tile next_tile_intended = position.getNextTile(intended_direction);

        //Dans le cas d'un tournant où on est pas deja en train de faire du cornering
        if(game_model.isTileLegal(next_tile_intended) && intended_direction!=direction && !turnaround() && cornering==false) {

            //Si pacman est pas centré horizontalement ou verticalement, il est en cornering
            if((position.isCenteredHorizontallyOnTile() || position.isCenteredVerticallyOnTile()) ){
               //Si pacman n'est pas au centre de la tile, il doit faire du cornering,
                //si il fait deja du cornering, pas besoin de modifier le cornering_direction

                //C'est imortant de set center passed avant de set cornering_direction
                //Et c'est important de set le cornering avant de mettre à jour la direction avec intended_direction
                setIsCenterPassed();
                setCornering();
                //std::cout<<"SET CORNERING"<<std::endl;
                if(cornering_direction!=Cornering::NONE){
                    direction = intended_direction;
                    memory_direction=intended_direction;
                }


            }
        }

        //Dans le cas d'un demi-tour, on ne peut le faire que au centre d'une tile
        if(game_model.isTileLegal(next_tile_intended) && intended_direction!=direction) {
            if(position.isCenteredOnTile()){
                direction = intended_direction;
                memory_direction=intended_direction;
            }
        }
    }

    //PacMan s'arrete quand la tile devant lui est illégale
    Tile next_tile = position.getNextTile(direction);
    if(!game_model.isTileLegal(next_tile) && position.isCenteredOnTile()){
        if(position.isCenteredOnTile())
            //std::cout<<"centered_on_tile"<<std::endl;
            direction = Direction::NONE;
    }


    /*Si Pacman est pas CenteredOnTile, ça veut dire qu'il est en train de faire du cornering
    Dans ce cas il garde la même direction*/
}

void PacMan::updatePosition()
{
    // Update the position based on the direction
    if(cornering_direction==PacMan::Cornering::NONE)
    {
        // Call parent function
        Character::updatePosition();
    }
     else
    {
        switch (cornering_direction) {
            case PacMan::Cornering::UP_LEFT:
                position += {-1,-1};
                break;
            case PacMan::Cornering::UP_RIGHT:
                position += {1,-1};
                break;
            case PacMan::Cornering::DOWN_LEFT:
                position += {-1,1};
                break;
            case PacMan::Cornering::DOWN_RIGHT:
                position += {1,1};
                break;
            default:
                break;
        }
    }
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

bool PacMan::isGameOver() const {
    return game_over;
}

void PacMan::setIsGameOver(bool game_over) {
    this->game_over = game_over;
}

void PacMan::printCornering() const
{
    switch (cornering_direction)
    {
    case Cornering::NONE:
        std::cout <<"cornering_direction: NONE"<< std::endl;
        break;
    case Cornering::UP_LEFT:
        std::cout <<"cornering_direction: UP_LEFT"<< std::endl;
        break;
    case Cornering::UP_RIGHT:
        std::cout <<"cornering_direction: UP_RIGHT"<< std::endl;
        break;
    case Cornering::DOWN_LEFT:
        std::cout <<"cornering_direction: DOWN_LEFT"<< std::endl;
        break;
    case Cornering::DOWN_RIGHT:
        std::cout <<"cornering_direction: DOWN_RIGHT"<< std::endl;
        break;
    default:
        break;
    }
}

int PacMan::getDotsEaten() const {
    return dots_eaten;
}

void PacMan::resetDotsEaten() {
    dots_eaten = 0;
}


Direction PacMan::getMemoryDirection() const
{
    return memory_direction;
}

void PacMan::setEnergized(bool energized)
{
    this->energized = energized;
}

bool PacMan::isEnergized() const
{
    return energized;
}

void PacMan::setMemoryDirection(Direction memory_direction)
{
    this->memory_direction = memory_direction;
}

void PacMan::die()
{
    game_over = true;
    lives--;
    direction = Direction::RIGHT;
    intended_direction = Direction::RIGHT;
    memory_direction = Direction::RIGHT;
}