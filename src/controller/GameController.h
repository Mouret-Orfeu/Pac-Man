#pragma once

#include <SDL.h>

class GameController {
public:
    GameController();
    ~GameController();

    bool init();
    void run();

    void limitFramerate(Uint64& frameStartTime);
private:
    bool sdl_initialized;
    
};
