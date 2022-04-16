#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <iostream>
#include <ncursesw/ncurses.h>

#include "entity/Entity.hpp"
#include "entity/Player.hpp"
#include "entity/Mob.hpp"

#include "map/Room.hpp"


// Prevent compiler from complaining.
class Player;


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

    /* Create window. */
    void createWindows();

    /* Draw action menu */
    void drawInteractionMenu();

    /* Draw map */
    void drawMap();
    
    /* Draw information in message queue */
    void drawMessageQueue();

    /* Draw everythings */
    void drawAll();

    /* Create a new player */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's iteraction with objects in that room */
    void handleInteraction();

    void pushActionMessage(std::string);

    /* 
     * Check is movement valid and modify entity's location 
     * And collision detection on Entity and RoomObject. */
    bool handleMovement(std::shared_ptr<Entity> entity, Location offset);

    Room& findRoomByName(std::string name) const;
    bool isValidLocation(Location location);

private:
    static uint32_t FRAME_WIDTH;
    static uint32_t FRAME_HEIGHT;
    static uint32_t FRAME_MAP_LOC_X;
    static uint32_t FRAME_MAP_LOC_Y;
    static uint32_t FRAME_MAP_WIDTH;
    static uint32_t FRAME_MAP_HEIGHT;
    static uint32_t FRAME_MSG_LOC_X;
    static uint32_t FRAME_MSG_LOC_Y;
    static uint32_t FRAME_MSG_WIDTH;
    static uint32_t FRAME_MSG_HEIGHT;
    static uint32_t FRAME_STAT_LOC_X;
    static uint32_t FRAME_STAT_LOC_Y;
    static uint32_t FRAME_STAT_WIDTH;
    static uint32_t FRAME_STAT_HEIGHT;
    static uint32_t FRAME_INT_LOC_X;
    static uint32_t FRAME_INT_LOC_Y;
    static uint32_t FRAME_INT_WIDTH;
    static uint32_t FRAME_INT_HEIGHT;

    WINDOW *map_window;
    WINDOW *message_window;
    WINDOW *status_window;
    WINDOW *interact_window;

    static std::unique_ptr<GameManager> g_instance;

    std::shared_ptr<Room> current_room;
    std::vector<std::shared_ptr<Room>> room_list;

    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Entity>> object_list;

    /* For action messages */
    std::queue<std::string> messsage_queue;
    std::vector<std::string> interact_options;
    // If all data is prepared, then set frame_ready = true;
    bool frame_ready;
    std::vector<std::vector<std::string>> frame_map_data;
};