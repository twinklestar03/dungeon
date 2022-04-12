#include <iostream>

#include "game/GameManager.hpp"


int main() {
    GameManager &gameManager = GameManager::getInstance();
    // Register game information.
    gameManager.init();
    // Spin up the game.
    gameManager.start();
    
    std::cout << "Hello World!" << std::endl;

    return 0;
}