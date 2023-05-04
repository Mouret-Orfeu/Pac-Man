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
 is_dead(false),
 cornering_direction(Cornering::NONE),
 cornering(false),
 is_center_passed(Center_passed::NOT_PASSED),
 dots_eaten(0)
{}

PacMan::~PacMan() {}

// Implement PacMan-specific methods here
void PacMan::move(int count) {
    (void)count;

    // WARNNING: we check too many things at each frame, this is not efficient

    // Eat dots and energizers
    eat();
    // if(position.isCenteredOnTile()){
    //     eat();
    // }

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
    switch (gameModel.getTile(current_tile)) {
        case GameModel::TileType::DOT:
            gameModel.setTile(current_tile, GameModel::TileType::EMPTY);
            score+=10;
            frames_to_drop = 1;
            dots_eaten++;
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

    //DEBUG
    //printDirection();

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
        if(gameModel.isTileLegal(next_tile_intended) && intended_direction!=direction && !turnaround() && cornering==false) {

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
                    sprite_orientation = intended_direction;
                }


            }
            //DEBUG
            //printCornering();
            //std::cout<<is_center_passed<<std::endl;
        }

        //Dans le cas d'un demi-tour, on ne peut le faireque au centre d'une tile
        if(gameModel.isTileLegal(next_tile_intended) && intended_direction!=direction) {
            if(position.isCenteredOnTile()){
                direction = intended_direction;
                sprite_orientation = intended_direction;
            }
        }
    }

    //DEBUG
    //printDirection();

    //PacMan s'arrete quand la tile devant lui est illégale
    Tile next_tile = position.getNextTile(direction);
    if(!gameModel.isTileLegal(next_tile) && position.isCenteredOnTile()){
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

bool PacMan::isDead() const {
    return is_dead;
}

void PacMan::setIsDead(bool is_dead) {
    this->is_dead = is_dead;
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
