#pragma once

#include "Character.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"

#include "common/GameDimensions.h"
#include "common/Direction.h"
#include "common/Position.h"

#include <array>
#include <memory>

class GameModel {
public:
    GameModel();
    ~GameModel();

    void update(Direction input_direction, int second_count);

    PacMan& getPacMan();
    std::array<std::unique_ptr<Ghost>, 2>& getGhosts();

    int getCount() const;
    void setCount(int count);

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

    void GhostSwitchMode(int second_count, std::array<std::unique_ptr<Ghost>, 2>& ghosts);

private:
    PacMan pacman;
    std::array<std::unique_ptr<Ghost>, 2> ghosts;
    int count;
    TileType tilesMatrix[WINDOW_ROWS][WINDOW_COLS];

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
