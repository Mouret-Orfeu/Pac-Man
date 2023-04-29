#pragma once

#include "Ghost.h"
#include "PacMan.h"

class GameModel {
public:
    GameModel();
    ~GameModel();

    void update(Character::Direction input_direction);

    Ghost& getGhost();
    PacMan& getPacMan();

    int getCount() const;
    void setCount(int count);


    int getScore() const;
    void setScore(int score);

    int getHighScore() const;
    void setHighScore(int highscore);

    int getLives() const;
    void setLives(int lives);

    bool getDeath() const;
    void setDeath(bool death);


    // Tile size
    static constexpr int TILE_SIZE = 8;

    // Dimensions
    static constexpr int COLS = 28,
                         ROWS = 36;
    static constexpr int MAZE_COLS = 28,
                         MAZE_ROWS = 31;
    static constexpr int WIDTH  = COLS*TILE_SIZE,
                         HEIGHT = ROWS*TILE_SIZE;

    // Maze cells
    enum class Cell {
        WALL = -1,
        EMPTY = 0,
        DOT = 1,
        POWER_PELLET = 2,
        // FRUIT = 3,
    };

    static constexpr Cell W = Cell::WALL;
    static constexpr Cell E = Cell::EMPTY;
    static constexpr Cell D = Cell::DOT;
    static constexpr Cell P = Cell::POWER_PELLET;

    // Maze layout
    static constexpr Cell TILES[ROWS][COLS] = {
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
        {W,D,D,D,D,D,D,D,D,D,D,D,D,W,W,D,D,D,D,D,D,D,D,D,D,D,D,W},
        {W,D,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,D,W},
        {W,P,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,P,W},
        {W,D,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,D,W},
        {W,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,W},
        {W,D,W,W,W,W,D,W,W,D,W,W,W,W,W,W,W,W,D,W,W,D,W,W,W,W,D,W},
        {W,D,W,W,W,W,D,W,W,D,W,W,W,W,W,W,W,W,D,W,W,D,W,W,W,W,D,W},
        {W,D,D,D,D,D,D,W,W,D,D,D,D,W,W,D,D,D,D,W,W,D,D,D,D,D,D,W},
        {W,W,W,W,W,W,D,W,W,W,W,W,E,W,W,E,W,W,W,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,W,W,W,E,W,W,E,W,W,W,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,E,E,E,E,E,E,E,E,E,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,W,W,W,W,W,W,W,W,E,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,W,W,W,W,W,W,W,W,E,W,W,D,W,W,W,W,W,W},
        {E,E,E,E,E,E,D,E,E,E,W,W,W,W,W,W,W,W,E,E,E,D,E,E,E,E,E,E},
        {W,W,W,W,W,W,D,W,W,E,W,W,W,W,W,W,W,W,E,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,W,W,W,W,W,W,W,W,E,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,E,E,E,E,E,E,E,E,E,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,W,W,W,W,W,W,W,W,E,W,W,D,W,W,W,W,W,W},
        {W,W,W,W,W,W,D,W,W,E,W,W,W,W,W,W,W,W,E,W,W,D,W,W,W,W,W,W},
        {W,D,D,D,D,D,D,D,D,D,D,D,D,W,W,D,D,D,D,D,D,D,D,D,D,D,D,W},
        {W,D,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,D,W},
        {W,D,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,D,W},
        {W,P,D,D,W,W,D,D,D,D,D,D,D,E,E,D,D,D,D,D,D,D,W,W,D,D,P,W},
        {W,W,W,D,W,W,D,W,W,D,W,W,W,W,W,W,W,W,D,W,W,D,W,W,D,W,W,W},
        {W,W,W,D,W,W,D,W,W,D,W,W,W,W,W,W,W,W,D,W,W,D,W,W,D,W,W,W},
        {W,D,D,D,D,D,D,W,W,D,D,D,D,W,W,D,D,D,D,W,W,D,D,D,D,D,D,W},
        {W,D,W,W,W,W,W,W,W,W,W,W,D,W,W,D,W,W,W,W,W,W,W,W,W,W,D,W},
        {W,D,W,W,W,W,W,W,W,W,W,W,D,W,W,D,W,W,W,W,W,W,W,W,W,W,D,W},
        {W,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,W},
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E}
    };
private:
    Ghost blinky;
    PacMan pacman;
    int count;
    int score = 33203;
    int highscore = 1323422;
    int lives = 3;
    bool death = false;
};
