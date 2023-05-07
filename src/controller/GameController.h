#pragma once

#include <SDL.h>

class GameController {
public:
    GameController();
    ~GameController();

    int getTimeCount() const;

    bool init();
    void run();

    void limitFramerate(Uint64& frameStartTime);
private:
    bool sdl_initialized;
    float time_count;

    //on compte le temps durant lequel les fantomes sont frightened
    float fright_time_count;
};
