#include <iostream>

#include "game/game.h"

int main(int argc, char *argv[]) {
    std::cout << "main()" << std::endl;
    game::Game game;
    game.run();
    std::cout << "finished()" << std::endl;
    return 0;
}
