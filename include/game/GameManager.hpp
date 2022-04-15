#pragma once
#include <queue>
#include <vector>
#include <memory>

#include "entity/Entity.hpp"
#include "entity/Player.hpp"

#include "map/Room.hpp"


class GameManager {
public:
    GameManager();
    ~GameManager();

    static GameManager& getInstance();

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void initGame();

    /* Tick the game, process events, entites think */
    void tickGame();

    /* Start the game process */
    void startGame();

    /* Create a new player */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's iteraction with objects in that room */
    void handleInteraction();

    void pushActionMessage(std::string);

    /* Check is movement valid and modify entity's location 
     * And collision detection on Entity and RoomObject.
     */
    void handleMovement(std::shared_ptr<Entity> entity, Location offset);

    /* Location handling */
    Room& findRoomByName(std::string name) const;
    bool isValidLocation(Location location);

private:
    static std::unique_ptr<GameManager> g_instance;

    std::shared_ptr<Room> current_room;
    std::vector<std::shared_ptr<Room>> room_list;

    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Object>> object_list;

    /* For action messages */
    std::queue<std::string> action_queue;
};