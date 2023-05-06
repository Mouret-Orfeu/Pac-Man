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

    //on compte le temps durant lequel les fantomes sont frightened
    float fright_time_count;
};
