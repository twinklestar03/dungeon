#include "game/GameManager.hpp"


std::unique_ptr<GameManager> GameManager::sInstance = nullptr;

GameManager& GameManager::getInstance() {
    if (sInstance == nullptr) {
        sInstance = std::make_unique<GameManager>();
    }
    return *sInstance;
}

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::init() {
    // Setup the stage
    std::unique_ptr<Room> room = std::make_unique<Room>("Test", 10, 10);
    std::cerr << "Test Room Creation.\n";
    room->generate();
    room->dumpMapInfo();
}

void GameManager::start() {

}   

void GameManager::tick() {
    // TODO: Player's move.

    // TODO: Iterate through all entities and call their tick function.
    /*for (auto it = this->entity_list.begin(); it != this->entity_list.end(); it++) {
        // Purge deleted entity.
        Entity& entity = **it;
        if ( entity.isDeleted() ) {
            this->entity_list.erase(it);
            continue;
        }
        
        if (entity.getType() == Entity::EntityType::MOB) {
            Mob& mob = dynamic_cast<Mob&>(entity);
            mob.think();
        }
    }*/

    render();
}

void GameManager::render() {
}