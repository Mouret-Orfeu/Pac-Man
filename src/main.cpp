#include "controller/GameController.h"

int main(int argc, char** argv) {
    GameController gameController;

    if (!gameController.init()) {
        return 1;
    }

    gameController.run();
    return 0;
}
