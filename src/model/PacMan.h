#pragma once

#include "Character.h"

class GameModel;

class PacMan : public Character {
public:

    /**
    * @brief Constructeur par defaut qui fait spawn pacman à sa position de départ standard et qui le fait partir sur la droite
    */
    PacMan(GameModel& gameModel);

    /*
    * @brief Constructeur qui permet de faire spawn pacman à une autre position
    */
    PacMan(SDL_Point pos_center);

    ~PacMan();

    void move(int count) override;

    void eat();

    /**
    * @brief  updateDirection permet de mettre à jour la direction et l'attribut "cornering_direction" de pacman
    * 
    */
    void updateDirection();
    void updatePosition();

    Direction getIntendedDirection() const;
    void setIntendedDirection(Direction direction);

    int getScore() const;
    void setScore(int score);

    int getHighScore() const;
    void setHighScore(int highscore);

    int getLives() const;
    void setLives(int lives);

    bool isDead() const;
    void setIsDead(bool death);

    void setIsCenterPassed();

    enum class Cornering {
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    NONE
    };

    enum class Center_passed {
    PASSED,
    NOT_PASSED,
    ON_CENTER
    };

    void setCornering();

    //DEBUG
    void printCornering() const;

    bool turnaround() const;

private:
    Direction intended_direction;
    int score;
    int highscore;
    int lives;
    bool is_dead;
    Cornering cornering_direction;
    bool cornering;

    //Pour savoir quel type de cornering il faut faire
    Center_passed is_center_passed;
};
