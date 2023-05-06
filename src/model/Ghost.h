#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/Tile.h"
#include "PacMan.h"

#include <iostream>
#include <SDL.h>
#include <vector>

class GameModel;

class Ghost : public Character {
public:
    enum class Type {
        BLINKY,
        PINKY,
        INKY,
        CLYDE
    };

    enum class Mode {
        SCATTER,
        CHASE,
        FRIGHTENED
    };

    //Les ghosts ont besoin d'un pacman pour calculer leur target tile
    Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile, bool out_of_den, PacMan& pacman);
    virtual ~Ghost();

    Type getType() const;

    void setMode(Mode mode);
    Mode getMode() const;

    Tile getScatterTargetTile() const;

    void setCurrentTargetTile(Tile tile);
    Tile getCurrentTargetTile() const;

    void updateDirection();

    virtual void leaveTheDen() =0;
    virtual void updateTargetTile() =0;

    void printType(Type ghost_type) const;

    void move(int count) override;

    void setModeHasChanged(bool mod_has_changed);
    bool getModeHasChanged() const;

    void setModeJustChanged(bool mod_just_changed);
    bool getModeJustChanged() const;

    

protected:
    Type ghost_type;
    Mode ghost_mode;

    Tile scatter_target_tile;
    Tile current_target_tile;

    std::vector<Tile> forbiden_tiles_UP={{13,12},{13,15}};
    std::vector<Tile> forbiden_tiles_DOWN={{25,12},{25,15}};

    Position out_of_den_position;
    Position center_den_position;

    bool out_of_den;

    PacMan& pacman;

    //vrai si le mod a changé depuis le début de la partie (se réinitialise quand le fantome meurt)
    bool mode_has_changed;

    //vrai si le mod vient de changé, devient quand le fantome atteint le prochain centre de tile
    bool mode_just_changed;
};
