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
 cornering(Cornering::NONE),
 center_passed(false)
{}

PacMan::~PacMan() {}

// Implement PacMan-specific methods here
void PacMan::move(int count) {
    (void)count;

    // Eat dots and power pellets
    if (position.isCenteredHorizontallyOnTile() || position.isCenteredVerticallyOnTile()) {
        eat();
        updateDirection();
    }

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    if (frames_to_drop > 0)
        frames_to_drop--;
    else
        updatePosition();
}

void PacMan::eat() {
    Tile current_tile = position.toTile();
    switch (gameModel.getTile(current_tile)) {
        case GameModel::TileType::DOT:
            gameModel.setTile(current_tile, GameModel::TileType::EMPTY);
            score+=10;
            frames_to_drop = 1;
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
                    if(center_passed)
                        cornering= Cornering::DOWN_LEFT;
                    else
                        cornering= Cornering::UP_LEFT;
                    break;
                case Direction::RIGHT:
                    if(center_passed)
                        cornering= Cornering::UP_LEFT;
                    else
                        cornering= Cornering::DOWN_RIGHT;
                    break;
                default:
                    break;
            }
        case Direction::DOWN:
            switch(intended_direction)
            {
                case Direction::LEFT:
                    if(center_passed)
                        cornering= Cornering::UP_LEFT;
                    else
                        cornering= Cornering::DOWN_LEFT;
                    break;
                case Direction::RIGHT:
                    if(center_passed)
                        cornering= Cornering::UP_RIGHT;
                    else
                        cornering= Cornering::DOWN_RIGHT;
                    break;
                default:
                    break;
            }
        case Direction::LEFT:
            switch(intended_direction)
            {
                case Direction::UP:
                    if(center_passed)
                        cornering= Cornering::UP_RIGHT;
                    else
                        cornering= Cornering::UP_LEFT; 
                    break;
                case Direction::DOWN:
                    if(center_passed)
                        cornering= Cornering::DOWN_RIGHT;
                    else
                        cornering= Cornering::DOWN_LEFT;
                    break;
                default:
                    break;
            }
        case Direction::RIGHT:
            switch(intended_direction)
            {
                case Direction::UP:
                    if(center_passed)
                        cornering= Cornering::UP_LEFT;
                    else
                        cornering= Cornering::UP_RIGHT;
                    break;
                case Direction::DOWN:
                    if(center_passed)
                        cornering= Cornering::DOWN_LEFT;
                    else
                        cornering= Cornering::DOWN_RIGHT;
                    break;
                default:
                    break;
            }
        default:
            break;
    }
    
}

void PacMan::setCenterPassed()
{
    switch (direction)
    {
    case Direction::UP:
        if(position.getY()>position.getCenterTile().y)
            center_passed=true;
        break;
    case Direction::DOWN:
        if(position.getY()<position.getCenterTile().y)
            center_passed=true;
        break;
    case Direction::LEFT:
        if(position.getX()<position.getCenterTile().x)
            center_passed=true;
        break;
    case Direction::RIGHT:
        if(position.getX()>position.getCenterTile().x)
            center_passed=true;
        break;
    default:
        center_passed=false;
        break;
    }
}

void PacMan::updateDirection() {

    //Si PacMan était en cornering et qu'il est centré horizontalement ou verticalement, le cornering est fini
    if(cornering!=Cornering::NONE && (position.isCenteredHorizontallyOnTile() || position.isCenteredVerticallyOnTile()))
        cornering=Cornering::NONE;
    
        

    //Si PacMan veut tourner dans une nouvelle direction:
    //Update the direction based on the intended direction
    //Update le cornering
    if (intended_direction != Direction::NONE) {
        Tile next_tile_intended = position.getNextTile(intended_direction);
        if(gameModel.isTileLegal(next_tile_intended) && intended_direction!=direction) {

            //C'est imortant de set center passed avant de set cornering
            //Et c'est important de set le cornering avant de mettre à jour la direction avec intended_direction
            setCenterPassed();
            setCornering();

            //DEBUG
            printCornering();

            direction = intended_direction;
            sprite_orientation = intended_direction;
        }


    }

    //PacMan s'arrete quand la tile devant lui est illégale
    Tile next_tile = position.getNextTile(direction);
    if(!gameModel.isTileLegal(next_tile) && position.isCenteredOnTile())
        direction = Direction::NONE;

    /*Si Pacman est pas CenteredOnTile, ça veut dire qu'il est en train de faire du cornering 
    Dans ce cas il garde la même direction*/
}

void PacMan::updatePosition()
{
    // Update the position based on the direction
    if(cornering==PacMan::Cornering::NONE)
    {
        switch (direction) {
            case Direction::UP:
                position.incrementY(-1);
                break;
            case Direction::DOWN:
                position.incrementY(1);
                break;
            case Direction::LEFT:
                position.incrementX(-1);
                break;
            case Direction::RIGHT:
                position.incrementX(1);
                break;
            default:
                break;
        } 
    }
    else
    {
        switch (cornering) {
            case PacMan::Cornering::UP_LEFT:
                position.incrementX(-1);
                position.incrementY(-1);
                break;
            case PacMan::Cornering::UP_RIGHT:
                position.incrementX(1);
                position.incrementY(-1);
                break;
            case PacMan::Cornering::DOWN_LEFT:
                position.incrementX(-1);
                position.incrementY(1);
                break;
            case PacMan::Cornering::DOWN_RIGHT:
                position.incrementX(1);
                position.incrementY(1);
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
    switch (cornering)
    {
    case Cornering::NONE:
        std::cout <<"cornering: NONE"<< std::endl;
        break;
    case Cornering::UP_LEFT:
        std::cout <<"cornering: UP_LEFT"<< std::endl;
        break;
    case Cornering::UP_RIGHT:
        std::cout <<"cornering: UP_RIGHT"<< std::endl;
        break;
    case Cornering::DOWN_LEFT:
        std::cout <<"cornering: DOWN_LEFT"<< std::endl;
        break;
    case Cornering::DOWN_RIGHT:
        std::cout <<"cornering: DOWN_RIGHT"<< std::endl;
        break;
    default:
        break;
    }
}

