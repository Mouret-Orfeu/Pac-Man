#pragma once

#include "Character.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "MonsterDen.h"

#include "common/GameDimensions.h"
#include "common/Direction.h"
#include "common/Position.h"

#include <array>
#include <memory>

class GameModel {
public:
    GameModel();
    ~GameModel();

    void update(Direction input_direction);

    PacMan& getPacMan();
    std::array<std::unique_ptr<Ghost>, 4>& getGhosts();

    int getFrameCount() const;

    // Maze cells
    enum class TileType {
        WALL = -1,
        EMPTY = 0,
        DOT = 1,
        ENERGIZER = 2,
        // FRUIT = 3,
    };

    // Getter and setter for tilesMatrix
    TileType getTile(Tile tile) const;
    void setTile(Tile tile, TileType value);

    /**
    * @brief Teste si la tile passé en argument est un mur (tile légale= tile qui n'est pas un mur)
    */
    bool isTileLegal(Tile tile);

    void updateGhostMode();

    bool getFrightenedBool() const;
    Uint64 getFrightenedCounter() const;

    float getLastTimeDotEatenTimer() const;
    void setLastTimeDotEatenTimer(float last_time_dot_eaten_timer);

    void HandlePacGhostCollision();


    /**
    * @brief QUand toutes les gommes sont mangées, on réinitialise tout sauf le hight score et les constantes de jeu
    */
    void reset();

    void resetTilesMatrix();

    void setTimeCount(float time_count);
    float getTimeCount() const;

    void setFrightTimeCount(float fright_time_count);
    float getFrightTimeCount() const;


    void setFrightenedCounter(Uint64 frightened_counter);

    int getNbDotTotal() const;

    bool getFruit() const;
    void setFruit(bool fruit);

    void setFrameFruit(int frame_fruit);

    void upDateFruit();

    Position getFruitPosition() const;

    bool getStartState() const;
    void setStartState(bool start_state);

    bool getGameOverState() const;
    void setGameOverState(bool game_over_state);

private:
    Uint64 frame_count;
    MonsterDen monster_den;
    PacMan pacman;
    std::array<std::unique_ptr<Ghost>, 4> ghosts;
    TileType tilesMatrix[WINDOW_ROWS][WINDOW_COLS];
    bool frightened_bool;
    Uint64 frightened_counter;
    float last_time_dot_eaten_timer;

    int nb_point_eat_ghost;

    float time_count;

    //on compte le temps durant lequel les fantomes sont frightened
    float fright_time_count;

    const int NB_DOT_TOTAL;

    bool fruit;
    int frame_fruit;
    Position fruit_position;

    bool start_state;
    bool game_over_state;

    // Maze layout
    static constexpr TileType W = TileType::WALL;
    static constexpr TileType E = TileType::EMPTY;
    static constexpr TileType D = TileType::DOT;
    static constexpr TileType Z = TileType::ENERGIZER;
    static constexpr TileType INITIAL_TILES_MATRIX[WINDOW_ROWS][WINDOW_COLS] = {
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
        {W,D,D,D,D,D,D,D,D,D,D,D,D,W,W,D,D,D,D,D,D,D,D,D,D,D,D,W},
        {W,D,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,D,W},
        {W,Z,W,W,W,W,D,W,W,W,W,W,D,W,W,D,W,W,W,W,W,D,W,W,W,W,Z,W},
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
        {W,Z,D,D,W,W,D,D,D,D,D,D,D,E,E,D,D,D,D,D,D,D,W,W,D,D,Z,W},
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
};
