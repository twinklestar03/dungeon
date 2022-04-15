#include <iostream>

#include "game/GameManager.hpp"


int main() {
    GameManager &gameManager = GameManager::getInstance();
    // Register game information.
    gameManager.initGame();
    // Spin up the game.
    gameManager.startGame();
    
    std::cout << "Hello World! ⚔️" << std::endl;

    return 0;
}