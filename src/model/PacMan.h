#pragma once

#include "Character.h"
//#include "MonsterDen.h"

class GameModel;
class MonsterDen;

class PacMan : public Character {
public:

    /**
    * @brief Constructeur par defaut qui fait spawn pacman à sa position de départ standard et qui le fait partir sur la droite
    */
    PacMan(GameModel& game_model, MonsterDen& monster_den);

    /*
    * @brief Constructeur qui permet de faire spawn pacman à une autre position
    */
    PacMan(SDL_Point pos_center);

    ~PacMan();

    void reset();

    void move(int count) override;

    void eat();

    /**
    * @brief  updateDirection permet de mettre à jour la direction et l'attribut "cornering_direction" de pacman
    *
    */
    void updateDirection() override;
    void updatePosition() override;

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

    int getDotsEaten() const;
    void resetDotsEaten();

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

    Direction getMemoryDirection() const;

    void setEnergized(bool energized);
    bool isEnergized() const;

    void setMemoryDirection(Direction direction);

    void die() override;

private:
    MonsterDen& monster_den;
    Direction intended_direction;
    int score;
    int highscore;
    int lives;
    bool is_dead;
    Cornering cornering_direction;
    bool cornering;

    //J'ai besoin de ça pour pouvoir calculer des target tile quand pacman.direction=NONE
    //memory direction est la même chose que direction seulement, elle n'est jamais à NONE
    Direction memory_direction;

    //Pour savoir quel type de cornering il faut faire
    Center_passed is_center_passed;
    int dots_eaten;

    bool energized;
};
