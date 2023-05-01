#pragma once

#include "Ghost.h"

#include "common/Position.h"

#include <SDL.h>

class GameModel;

class Clyde : public Ghost {
public:
    Clyde(GameModel& gameModel);
    ~Clyde();

    void move(int count) override;

    Type getType() const override;
};
