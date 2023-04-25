#pragma once

class GameController {
public:
    GameController();
    ~GameController();

    bool init();
    void run();
private:
    bool sdl_initialized;
};
