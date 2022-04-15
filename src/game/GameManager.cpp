#include "game/GameManager.hpp"


std::unique_ptr<GameManager> GameManager::g_instance = nullptr;
uint32_t GameManager::FRAME_WIDTH = 80;
uint32_t GameManager::FRAME_HEIGHT = 40;
uint32_t GameManager::FRAME_MAP_LOC_X = 0;
uint32_t GameManager::FRAME_MAP_LOC_Y = 0;
uint32_t GameManager::FRAME_MAP_WIDTH = 0;
uint32_t GameManager::FRAME_MAP_HEIGHT = 0;
uint32_t GameManager::FRAME_MSG_LOC_X = 0;
uint32_t GameManager::FRAME_MSG_LOC_Y = 0;
uint32_t GameManager::FRAME_MSG_WIDTH = 0;
uint32_t GameManager::FRAME_MSG_HEIGHT = 0;
uint32_t GameManager::FRAME_STAT_LOC_X = 0;
uint32_t GameManager::FRAME_STAT_LOC_Y = 0;
uint32_t GameManager::FRAME_STAT_WIDTH = 0;
uint32_t GameManager::FRAME_STAT_HEIGHT = 0;
uint32_t GameManager::FRAME_ACT_LOC_X = 0;
uint32_t GameManager::FRAME_ACT_LOC_Y = 0;
uint32_t GameManager::FRAME_ACT_WIDTH = 0;
uint32_t GameManager::FRAME_ACT_HEIGHT = 0;

GameManager& GameManager::getInstance() {
    if (g_instance == nullptr) {
        g_instance = std::make_unique<GameManager>();
    }
    return *g_instance;
}

GameManager::GameManager() {
    frame_data = std::vector<std::vector<std::string>>(GameManager::FRAME_HEIGHT, std::vector<std::string>(GameManager::FRAME_WIDTH, ""));
}

GameManager::~GameManager() {
}

void GameManager::createWindows() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, FRAME_HEIGHT, FRAME_WIDTH);

    // Top right.
    FRAME_STAT_WIDTH = 55;
    FRAME_STAT_HEIGHT = FRAME_HEIGHT / 3;
    FRAME_STAT_LOC_X = FRAME_WIDTH - FRAME_STAT_WIDTH;
    FRAME_STAT_LOC_Y = 0;
    // Bottom right.
    FRAME_MSG_WIDTH = FRAME_STAT_WIDTH;
    FRAME_MSG_HEIGHT = FRAME_HEIGHT - FRAME_STAT_HEIGHT;
    FRAME_MSG_LOC_X = FRAME_WIDTH - FRAME_STAT_WIDTH;
    FRAME_MSG_LOC_Y = FRAME_STAT_HEIGHT;
    // bottom left.
    FRAME_ACT_WIDTH = FRAME_WIDTH - FRAME_STAT_WIDTH;
    FRAME_ACT_HEIGHT = (FRAME_HEIGHT / 4 < 10) ? 10 : FRAME_HEIGHT / 4;
    FRAME_ACT_LOC_X = 0;
    FRAME_ACT_LOC_Y = FRAME_HEIGHT - FRAME_ACT_HEIGHT;
    // Top Left.
    FRAME_MAP_WIDTH = FRAME_ACT_WIDTH;
    FRAME_MAP_HEIGHT = FRAME_HEIGHT - FRAME_ACT_HEIGHT;
    FRAME_MAP_LOC_X = 0;
    FRAME_MAP_LOC_Y = 0;

    map_window = newwin(FRAME_MAP_HEIGHT, FRAME_MAP_WIDTH, FRAME_MAP_LOC_Y, FRAME_MAP_LOC_X);
    message_window = newwin(FRAME_MSG_HEIGHT, FRAME_MSG_WIDTH, FRAME_MSG_LOC_Y, FRAME_MSG_LOC_X);
    status_window = newwin(FRAME_STAT_HEIGHT, FRAME_STAT_WIDTH, FRAME_STAT_LOC_Y, FRAME_STAT_LOC_X);
    action_window = newwin(FRAME_ACT_HEIGHT, FRAME_ACT_WIDTH, FRAME_ACT_LOC_Y, FRAME_ACT_LOC_X);
    
    wborder(map_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(status_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(action_window, '|', '|', '-', '-', '+', '+', '+', '+');

    wnoutrefresh(map_window);
    wnoutrefresh(message_window);
    wnoutrefresh(status_window);
    wnoutrefresh(action_window);
    doupdate(); 
    //mnoecho();
}

void GameManager::createMap() {
    std::shared_ptr<Room> lobby = std::make_shared<Room>("Lobby", "Room Object", 15, 15);
    room_list.push_back(lobby);

    // Generate entities (Mobs, Portals, NPCs).
    std::shared_ptr<Mob> mob = std::make_shared<Mob>("Slime", "A normal silme", Location(lobby->getName(), 3, 3));
    object_list.push_back(mob);
    
    std::shared_ptr<Room> mob_room_1 = std::make_shared<Room>("Mob Room 1", "Room Object", 20, 10);
    room_list.push_back(mob_room_1);
}

void GameManager::createPlayer() {
    std::string name = "Test Player";

    player = std::make_shared<Player>(name, "Player", Location(room_list[0]->getName(), 2, 2));

    assert(player != nullptr);
    // TODO: Ask attributes
}

void GameManager::handleInteraction() {
    // Draw interaction window.
    action_options.clear();
    action_options.push_back("    Actions:");
    action_options.push_back("        >> Movement (⬆️: up, ⬇️:down, ⬅️:left, ➡️: right");
    action_options.push_back("        c. Interact");
    action_options.push_back("        i. Inventory");
    drawAll();

    char ch;
    ch = wgetch(action_window);

    if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN) {
        uint32_t x = 0, y = 0;

        switch(ch) {
        case KEY_LEFT:
            x = -1;
            break;
        case KEY_RIGHT:
            x = 1;
            break;
        case KEY_UP:
            y = -1;
            break;
        case KEY_DOWN:
            y = 1;
            break;	
        }

        if(handleMovement(player, Location(x, y))) {
            pushActionMessage("You moved.");
        } else {
            pushActionMessage("You cannot pass through that thing.");
        }

        drawAll();
        return;

    } else if (ch == 'c') {
        // Get list of objects can be access by player
        std::vector<std::shared_ptr<Entity>> assessible;
        for (auto it = object_list.begin(); it != object_list.end(); it++) {
            if ((**it).getLocation().distance(player->getLocation()) <= 1) {
                assessible.push_back(*it);
            }
        }
    } else if (ch == 'i') {
    
    }
    


    
    
    // uint32_t choice = 0;
    // //std::cin >> choice;
    // if (choice == 1) {
    //         
    //         std::string direction;
    //         std::cout << "Direction (w,s,a,d) > ";
    //         std::cin >> direction;
    //         if (direction == "w") {
    //             y = -1;
    //         } else if (direction == "s") {
    //             y = 1;
    //         } else if (direction == "a") {
    //             x = -1;
    //         } else if (direction == "d") {
    //             x = 1;
    //         }
    //         if(handleMovement(player, Location(x, y))) {
    //             std::cout << "Movement Success" << std::endl;
    //             showMap();
    //         } else {
    //             std::cout << "Movement Failed" << std::endl;
    //         }
    //         return;

    // } else if (choice == 2) {
    //     std::cout << "Available actions: " << std::endl;
    //     for (auto i = 0; i < assessible.size(); i++) {
    //         std::string action;
    //         switch( assessible[i]->getType() ) {
    //             case Entity::EntityType::DOOR:
    //                 action = "🔓Open";
    //                 break;
    //             case Entity::EntityType::ITEM:
    //                 action = "🫴Pick up";
    //                 break;
    //             case Entity::EntityType::MOB:
    //                 action = "⚔️Attack";
    //                 break;
    //             case Entity::EntityType::NPC:
    //                 action = "🗣Talk";
    //                 break;
    //             case Entity::EntityType::PORTAL:
    //                 action = "💡Teleport";
    //                 break;
    //             case Entity::EntityType::SIGN:
    //                 action = "🔍Inspect";
    //                 break;
    //             default:
    //                 action = "❌Broken la";
    //                 break;
    //         }
    //         std::cout << i << ". " << action << " " << assessible[i]->getName() << std::endl;
    //     }
    //     uint32_t action;
    //     std::cout << "Choose an action > ";
    //     std::cin >> action;
    //     if (action < assessible.size() || action >= 0) {
    //         assessible[action]->interact(*player);
    //     }
    //     else {
    //         std::cout << "Invalid action..." << std::endl;
    //     }
    // } else if (choice == 3) {
    //     showMap();
    // }
}  

void GameManager::drawMap() {
    Room &room = findRoomByName(player->getLocation().getRoomName());
    
    // Draw RoomObject.
    int32_t lx = player->getLocation().getX() - FRAME_MAP_WIDTH / 2 - 1;
    int32_t rx = player->getLocation().getX() + FRAME_MAP_WIDTH / 2;
    int32_t ly = player->getLocation().getY() - FRAME_MAP_HEIGHT / 2 - 1;
    int32_t ry = player->getLocation().getY() + FRAME_MAP_HEIGHT / 2;
    for (auto i = ly, fi = 0; i < ry; ++i, ++fi) {
        for (auto j = lx, fj = 0; j < rx; ++j, ++fj) {
            if (i < 0 || j < 0 || i >= room.getMaxY() || j >= room.getMaxY()) {
                frame_data[fi][fj] = "  ";
            } else {
                frame_data[fi][fj] = room.getRoomObject({(uint32_t)i, (uint32_t)j})->getIcon();
            }
        }
    }

    // Draw Player.
    frame_data[player->getLocation().getY() - ly][player->getLocation().getX() - lx] = player->getIcon();

    // Draw other objects.
    for (auto it = object_list.begin(); it != object_list.end(); it++) {
        // Put object icon into frame_data if it is in the same room with player.
        if ((**it).getLocation().getRoomName() == player->getLocation().getRoomName()) {
            frame_data[(**it).getLocation().getY() - ly][(**it).getLocation().getX() - lx] = (**it).getIcon();
        }
    }

    // Update window.
    for (auto i = 0; i < FRAME_MAP_HEIGHT; ++i) {
        for (auto j = 0; j < FRAME_MAP_WIDTH; ++j) {
            mvwprintw(map_window, i, j, frame_data[i][j].c_str());
        }
    }
    wborder(map_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(map_window);

}

void GameManager::drawInteractionMenu() {
    wborder(action_window, '|', '|', '-', '-', '+', '+', '+', '+');

    uint32_t h = 1, w = 1;
    for (auto it = action_options.begin(); it != action_options.end(); it++) {
        if ((*it).size() > FRAME_ACT_WIDTH-2) {
            mvwprintw(action_window, h++, w, (*it).substr(0, FRAME_ACT_WIDTH-2).c_str());
            std::string rem = (*it).substr(FRAME_ACT_WIDTH-2);
            while (rem.size() > 0) {
                if (rem.size() > FRAME_ACT_WIDTH - 2) {
                    mvwprintw(action_window, h++, w, rem.substr(0, FRAME_ACT_WIDTH-3).c_str());
                    rem = rem.substr(FRAME_ACT_WIDTH-2);
                }
                else {
                    mvwprintw(action_window, h++, w, rem.c_str());
                    rem = "";
                }
            }
        }
        else {
            mvwprintw(action_window, h++, w, (*it).c_str());
        }
    }

    wrefresh(action_window);
}

void GameManager::drawMessageQueue() {
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    uint32_t h = 1, w = 1;

    while (messsage_queue.size() > 0) {
        if (messsage_queue.size() > 5) {
            while (messsage_queue.size() > 5) {
                messsage_queue.pop();
            }
        }

        std::queue<std::string> tmp_queue = messsage_queue;
        while (!tmp_queue.empty()) {
            if (tmp_queue.front().size() > FRAME_MSG_WIDTH-2) {
                mvwprintw(message_window, h++, w, tmp_queue.front().substr(0, FRAME_MSG_WIDTH-2).c_str());
                std::string rem = tmp_queue.front().substr(FRAME_MSG_WIDTH-2);
                while (rem.size() > 0) {
                    if (rem.size() > FRAME_MSG_WIDTH - 2) {
                        mvwprintw(message_window, h++, w, rem.substr(0, FRAME_MSG_WIDTH-3).c_str());
                        rem = rem.substr(FRAME_MSG_WIDTH-2);
                    }
                    else {
                        mvwprintw(message_window, h++, w, rem.c_str());
                        rem = "";
                    }
                }
            }
            else {
                mvwprintw(message_window, h++, w, tmp_queue.front().c_str());
            }
            tmp_queue.pop();
        }
    }
    

    wrefresh(message_window);
}

void GameManager::drawAll() {
    drawMap();
    drawInteractionMenu();
    drawMessageQueue();
}

bool GameManager::handleMovement(std::shared_ptr<Entity> entity, Location offset) {
    if (entity == nullptr) {
        return false;
    }

    std::shared_ptr<RoomObject> room_object = findRoomByName(entity->getLocation().getRoomName())
                                                .getRoomObject(entity->getLocation()+offset);

    if (room_object == nullptr) {
        return false;
    }

    if (room_object->canWalk()) {
        entity->setLocation(entity->getLocation() + offset);
        return true;
    }

    return false;
}

void GameManager::initGame() {
    createWindows();
    createMap();
    createPlayer();
}

void GameManager::tickGame() {
    handleInteraction();
    // TODO: invoke Mob AI.
}

void GameManager::startGame() {
    while(true) {
        tickGame();
    }
}

void GameManager::pushActionMessage(std::string message) {
    messsage_queue.push(message);
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