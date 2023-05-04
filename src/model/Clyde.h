#pragma once

#include "Ghost.h"

#include "common/Position.h"

#include <SDL.h>

class GameModel;

class Clyde : public Ghost {
public:
    Clyde(GameModel& gameModel);
    ~Clyde();

    void updateDirection() override;

    void move(int count) override;
};
