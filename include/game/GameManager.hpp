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

    static GameManager& getInstance();

    /* Entity Management */    
    // Spawn Entity at specific location.
    void spawnEntity(Location location, Entity& entitiy);

    // Get entities around a location.
    std::unique_ptr<std::vector<Entity>> getSurroundingEntities(Location location, uint32_t radius);

    /* Event Handling */
    void processEvents();

    /* General */
    void init();
    void start();
    /* Tick the game, process events, entites think */
    void tick();
    /* Render informations */
    void render();

private:
    static std::unique_ptr<GameManager> sInstance;
    std::vector<Room> rooms;

    std::unique_ptr<Player> local_player;
    std::vector<std::unique_ptr<Entity>> entity_list;

    std::queue<Event> event_queue;
};