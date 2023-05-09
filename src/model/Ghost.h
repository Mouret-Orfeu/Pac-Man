#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/Tile.h"
#include "PacMan.h"

#include <iostream>
#include <SDL.h>
#include <vector>

class PacMan;

class GameModel;

class Ghost : public Character {
public:

    //!!Ne pas changer l'ordre des types!! (utilisé dans MonsterDen::updateMonsterDen())
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
    Ghost(GameModel& game_model, Type ghost_type, Position spawn_position,Position respawn_position, Direction respawn_direction, Tile scatter_target_tile, bool out_of_den, PacMan& pacman, MonsterDen& monster_den);
    virtual ~Ghost();

    virtual void reset();

    Type getType() const;

    void setMode(Mode mode);
    Mode getMode() const;

    Tile getScatterTargetTile() const;

    void setCurrentTargetTile(Tile tile);
    Tile getCurrentTargetTile() const;

    void updateDirection();

    void switchModeFrightened(float time_count, float fright_time_count, bool frightened_bool);

    void cancelModeFrightened(float time_count, float fright_time_count, bool frightened_bool);

    void virtual TimeBasedModeUpdate(float time_count, float fright_time_count, bool frightened_bool);

    virtual void leaveTheDen() =0;
    virtual void updateTargetTile() =0;
    virtual void updateSpeed();

    void printType(Type ghost_type) const;

    void move() override;

    void setModeHasChanged(bool mod_has_changed);
    bool getModeHasChanged() const;

    void setModeJustChanged(bool mod_just_changed);
    bool getModeJustChanged() const;

    void setPreviousMode(Mode previous_ghost_mode);
    Mode getPreviousMode() const;

    void setOutOfDen(bool out_of_den);
    bool isOutOfDen();

    Direction getSpawnDirection() const;

    Position getSpawnPosition() const;

    Position getRespawnPosition() const;

    void resetMode();

    virtual void die() override;

    void setNormalSpeed(int normal_speed);

protected:
    Type ghost_type;
    Mode ghost_mode;

    Tile scatter_target_tile;
    Tile current_target_tile;

    std::vector<Tile> forbiden_tiles_UP;
    std::vector<Tile> forbiden_tiles_DOWN;
    const Tile Slowing_tile_right;
    const Tile Slowing_tile_left;

    Position out_of_den_position;
    Position center_den_position;

    bool out_of_den;

    PacMan& pacman;
    MonsterDen& monster_den;

    //vrai si le mod a changé depuis le début de la partie (se réinitialise quand le fantome meurt)
    bool mode_has_changed;

    //vrai si le mod vient de changé, devient quand le fantome atteint le prochain centre de tile
    bool mode_just_changed;

    //previews_ghost_mode va enregistrer le mode avant de passer en mode frightened, pour pouvoir y revenir après
    Mode previous_ghost_mode;

    Direction spawn_direction;
    Position spawn_position;
    Position respawn_position;

    int normal_speed;

    bool is_in_tunnel;
    bool normal_speed_changed;
};
