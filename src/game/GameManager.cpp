#include "game/GameManager.hpp"


std::unique_ptr<GameManager> GameManager::g_instance = nullptr;

GameManager& GameManager::getInstance() {
    if (g_instance == nullptr) {
        g_instance = std::make_unique<GameManager>();
    }
    return *g_instance;
}

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::createMap() {
    
}

void GameManager::createPlayer() {
    //player = std::make_shared<Player>();
}

void GameManager::handleInteraction() {

}

void GameManager::initGame() {
    createMap();
    createPlayer();
}

void GameManager::tickGame() {
    handleInteraction();
}

void GameManager::startGame() {
    
}

Room& GameManager::findRoomByName(std::string name) const {
    for (auto& room : room_list) {
        if (room->getName() == name) {
            return *room;
        }
    }
    return *current_room;
}

bool GameManager::isValidLocation(Location location) {
    const Room& room = findRoomByName(location.getRoomName());

    if (location.getX() > room.getMaxX() || location.getY() > room.getMaxY()) {
        return false;
    }

    if (location.getX() < 0 || location.getY() < 0) {
        return false;
    }

    return true;
}