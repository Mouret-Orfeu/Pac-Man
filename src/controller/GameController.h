#pragma once

#include "model/GameModel.h"
#include "view/GameView.h"

#include <SDL.h>

class GameController {
public:
    GameController();
    ~GameController();

    bool init();
    void run();

    void limitFramerate();
private:
    GameModel gameModel;
    GameView gameView;
    bool sdl_initialized;
    Uint64 gameStartTime;
    Uint64 total_frame_count;
};
