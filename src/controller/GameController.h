#pragma once

class GameController {
public:
    GameController();
    ~GameController();

    int getTimeCount() const;

    bool init();
    void run();
private:
    bool sdl_initialized;
    float time_count;
};
