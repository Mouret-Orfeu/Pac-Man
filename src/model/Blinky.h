#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "PacMan.h"
#include "MonsterDen.h"

#include <SDL.h>

class GameModel;

class Blinky : public Ghost {
public:
    Blinky(GameModel& game_model, PacMan& pacman, MonsterDen& monster_den);
    ~Blinky();

    

    void leaveTheDen() override;

    void updateTargetTile() override;


private:
    //pour l'instant je met 1, 2, 3 mais faudra mettre les vraies vitesse (vitesse2 c'est celle de PacMan)
    int vitesse1;
    int vitesse2;
    int vitesse3;
    Position respawn_position;
};
