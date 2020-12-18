#include <iostream>

#include "engine/engine.h"

int main(int argc, char *argv[]) {
    std::cout << "main()" << std::endl;
    Engine engine;
    std::cout << "main2()" << std::endl;
    engine.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
