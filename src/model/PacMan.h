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
    void updateDirection();

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

private:
    Direction intended_direction;
    int score;
    int highscore;
    int lives;
    bool is_dead;
};
