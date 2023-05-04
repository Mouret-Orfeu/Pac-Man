#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "PacMan.h"

#include <SDL.h>

class GameModel;

class Blinky : public Ghost {
public:
    Blinky(GameModel& gameModel, PacMan& pacman);
    ~Blinky();

    void move(int count) override;

    void leaveTheDen() override;

    void updateTargetTile() override;


private:
    //pour l'instant je met 1, 2, 3 mais faudra mettre les vraies vitesse (vitesse2 c'est celle de PacMan)
    int vitesse1;
    int vitesse2;
    int vitesse3;
    Position respawn_position;
};
