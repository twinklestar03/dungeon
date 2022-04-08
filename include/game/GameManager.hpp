#pragma once
#include <queue>
#include <vector>

#include "entity/Entity.hpp"
#include "entity/Mob.hpp"
#include "entity/Player.hpp"

#include "event/Event.hpp"
#include "game/Room.hpp"


class GameManager {
public:
    GameManager();
    ~GameManager();

    static GameManager& getInstance() {
        if (sInstance == nullptr) {
            sInstance = std::make_unique<GameManager>();
        }
        return *sInstance;
    }
    
    // If we have a listener design.
    //void registerEvent(Event& event);
    void queueEvent(Event& event);

    // Spawn Entity at specific location.
    void spawnEntity(Location location, Entity entitiy);

    std::unique_ptr<std::vector<Entity>> getSurroundingEntities(Location location, uint32_t radius);

    /* Load objects */
    /* Map generation */
    void generateMap();
    
    void init();

    void start();
    /* Tick the game, process events, entites think */
    void tick();
    /* Render informations */
    void render();

private:
    static std::unique_ptr<GameManager> sInstance;

    std::vector<Room> rooms;

    std::vector<Entity> entity_list;

    std::queue<Event> eventQueue;
};