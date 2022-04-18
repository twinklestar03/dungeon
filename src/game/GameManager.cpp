#include "game/GameManager.hpp"

#include "entity/Mob.hpp"
#include "entity/Portal.hpp"


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
uint32_t GameManager::FRAME_INT_LOC_X = 0;
uint32_t GameManager::FRAME_INT_LOC_Y = 0;
uint32_t GameManager::FRAME_INT_WIDTH = 0;
uint32_t GameManager::FRAME_INT_HEIGHT = 0;

GameManager& GameManager::getInstance() {
    if (g_instance == nullptr) {
        g_instance = std::make_unique<GameManager>();
    }
    return *g_instance;
}

GameManager::GameManager() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    //keypad(stdscr, TRUE);
    getmaxyx(stdscr, FRAME_HEIGHT, FRAME_WIDTH);
}

GameManager::~GameManager() {
}

void GameManager::createWindows() {
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
    FRAME_INT_WIDTH = FRAME_WIDTH - FRAME_STAT_WIDTH;
    FRAME_INT_HEIGHT = (FRAME_HEIGHT / 4 < 10) ? 10 : FRAME_HEIGHT / 4;
    FRAME_INT_LOC_X = 0;
    FRAME_INT_LOC_Y = FRAME_HEIGHT - FRAME_INT_HEIGHT;
    // Top Left.
    FRAME_MAP_WIDTH = FRAME_INT_WIDTH;
    FRAME_MAP_HEIGHT = FRAME_HEIGHT - FRAME_INT_HEIGHT;
    FRAME_MAP_LOC_X = 0;
    FRAME_MAP_LOC_Y = 0;

    map_window = newwin(FRAME_MAP_HEIGHT, FRAME_MAP_WIDTH, FRAME_MAP_LOC_Y, FRAME_MAP_LOC_X);
    message_window = newwin(FRAME_MSG_HEIGHT, FRAME_MSG_WIDTH, FRAME_MSG_LOC_Y, FRAME_MSG_LOC_X);
    status_window = newwin(FRAME_STAT_HEIGHT, FRAME_STAT_WIDTH, FRAME_STAT_LOC_Y, FRAME_STAT_LOC_X);
    interact_window = newwin(FRAME_INT_HEIGHT, FRAME_INT_WIDTH, FRAME_INT_LOC_Y, FRAME_INT_LOC_X);
    
    frame_map_data = std::vector<std::vector<std::string>>(GameManager::FRAME_MAP_HEIGHT, std::vector<std::string>(GameManager::FRAME_MAP_WIDTH, " "));

    wborder(map_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(status_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(interact_window, '|', '|', '-', '-', '+', '+', '+', '+');

    wnoutrefresh(map_window);
    wnoutrefresh(message_window);
    wnoutrefresh(status_window);
    wnoutrefresh(interact_window);
    doupdate(); 
    //mnoecho();
}

void GameManager::createMap() {
    // Room initialization.
    std::shared_ptr<Room> lobby = std::make_shared<Room>("Lobby", "Room Object", 15, 15);
    std::shared_ptr<Room> mob_room_1 = std::make_shared<Room>("Room_1", "Room Object", 20, 10);
    room_list.push_back(lobby);
    room_list.push_back(mob_room_1);

    // Generate entities (Mobs, Portals, NPCs).
    std::shared_ptr<Mob> mob = std::make_shared<Mob>("🤢", "Slime", "A normal silme", Location(lobby->getName(), 3, 3));
    object_list.push_back(mob);
    mob = std::make_shared<Mob>("🤢", "Slime", "A normal silme", Location(lobby->getName(), 8, 4));
    object_list.push_back(mob);
    mob = std::make_shared<Mob>("🤢", "Slime", "A normal silme", Location(lobby->getName(), 12, 9));
    object_list.push_back(mob);
    
    std::shared_ptr<Portal> portal_1 = std::make_shared<Portal>("To Room 1", "Portal Object", Location(lobby->getName(), 10, 10), Location(mob_room_1->getName(), 3, 3));
    object_list.push_back(portal_1);
}

void GameManager::createPlayer() {
    std::string name = "Test Player";

    player = std::make_shared<Player>(name, "Player", Location(room_list[0]->getName(), 2, 2));

    // TODO: Ask attributes
}

void GameManager::handleInteraction() {
    // Draw interaction window.
    interact_options.clear();
    interact_options.push_back(">> Movement (W: up, S:down, A:left, D: right");
    interact_options.push_back("c. Interact With Surroundings");
    interact_options.push_back("f. Inspect Objects");
    interact_options.push_back("i. Inventory");
    drawAll();

    // Loop until we get a valid input.
    uint32_t ch = 0;
    while (ch != 'w' && ch != 's' && ch != 'a' && ch != 'd' && ch != 'c' && ch != 'i') {
        ch = mvwgetch(interact_window, 1, 1);

        if (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd') {
            int x = 0, y = 0;
            if (ch == 'w') {
                y = -1;
            }
            else if (ch == 's') {
                y = 1;
            }
            else if (ch == 'a') {
                x = -1;
            }
            else if (ch == 'd') {
                x = 1;
            }

            if(handleMovement(player, Location(x, y))) {
                pushActionMessage("You moved.");
            } else {
                pushActionMessage("You can't move there.");
            }
        }
        else if (ch == 'c') {
            // Get list of objects can be access by player
            std::vector<std::shared_ptr<Entity>> assessible;
            for (auto it = object_list.begin(); it != object_list.end(); it++) {
                if (player->getLocation().distance((*it)->getLocation()) <= 1.5) {
                    assessible.push_back(*it);
                }
            }

            if (assessible.size() < 1) {
                pushActionMessage("There is nothing to interact with.");
                drawAll();
                return;
            }

            interact_options.clear();
    
            for (size_t i = 0; i < assessible.size(); i++) {
                std::string action;
                switch( assessible[i]->getType() ) {
                    case Entity::EntityType::DOOR:
                        action = "🔓Open";
                        break;
                    case Entity::EntityType::ITEM:
                        action = "🫴Pick up";
                        break;
                    case Entity::EntityType::MOB:
                        action = "⚔️Attack";
                        break;
                    case Entity::EntityType::NPC:
                        action = "🗣Talk";
                        break;
                    case Entity::EntityType::PORTAL:
                        action = "💡Teleport";
                        break;
                    case Entity::EntityType::SIGN:
                        action = "🔍Inspect";
                        break;
                    default:
                        action = "❌Broken la";
                        break;
                }
                interact_options.push_back(std::to_string(i) + ". " + action + " " + assessible[i]->getName());
            }
            interact_options.push_back("q. Leave interact");

            // Draw informations.
            drawAll();

            ch = mvwgetch(interact_window, 1, 1);
           
            if (ch - '0' < assessible.size() && ch - '0' >= 0) {
                assessible[ch - '0']->interact(*player);
                std::cerr << "Player location: " << player->getLocation().getRoomName() << " " << player->getLocation().getX() << " " << player->getLocation().getY() << std::endl;
                return;
            }
            else if (ch == 'q') {
                pushActionMessage("You leave the interact menu");
                return;
            }
            
            pushActionMessage("Invalid action...");
            return;

        }
        else if (ch == 'i') {
            
        }

        return;
    }
}  

void GameManager::drawMap() {
    std::shared_ptr<Room> room = findRoomByName(player->getLocation().getRoomName());
    if (room == nullptr) {
        pushActionMessage("[ERROR] [GameManager::drawMap]: Room not found.");
        return;
    }
    
    // Draw RoomObject.
    int32_t lx = player->getLocation().getX() - FRAME_MAP_WIDTH / 2 - 1;
    int32_t rx = player->getLocation().getX() + FRAME_MAP_WIDTH / 2;
    int32_t ly = player->getLocation().getY() - FRAME_MAP_HEIGHT / 2 - 1;
    int32_t ry = player->getLocation().getY() + FRAME_MAP_HEIGHT / 2;
    int32_t max_y = room->getMaxHeight();
    int32_t max_x = room->getMaxWidth();

    for (auto i = ly, fi = 0; i < ry && fi < FRAME_MAP_HEIGHT; ++i, ++fi) {
        for (auto j = lx, fj = 0; j < rx && fj < FRAME_MAP_WIDTH; ++j, ++fj) {
            // If we trying to draw a frame that is out of the room, draw nothing.
            if (i < 0 || j < 0 || i >= max_y || j >= max_x) {
                frame_map_data[fi][fj] = "  ";
            } else {
                frame_map_data[fi][fj] = room->getRoomObject({(uint32_t)i, (uint32_t)j})->getIcon();
            }
        }
    }

    // Draw Player.
    frame_map_data[player->getLocation().getY() - ly][player->getLocation().getX() - lx] = player->getIcon();

    // Draw other objects.
    for (auto it = object_list.begin(); it != object_list.end(); it++) {
        // Put object icon into frame_map_data if it is in the same room with player.
        if ((**it).getLocation().getRoomName() == player->getLocation().getRoomName()) {
            frame_map_data[(**it).getLocation().getY() - ly][(**it).getLocation().getX() - lx] = (**it).getIcon();
        }
    }

    // Update window.
    for (uint32_t i = 0; i < FRAME_MAP_HEIGHT; ++i) {
        for (uint32_t j = 0; j < FRAME_MAP_WIDTH; ++j) {
            mvwprintw(map_window, i, j, frame_map_data[i][j].c_str());
            
        }
    }
    wborder(map_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wnoutrefresh(map_window);

}

void GameManager::drawInteractionMenu() {
    uint32_t line = 1, indent = 4;
    wborder(interact_window, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(interact_window, line++, indent, "Actions:");
    for (auto it = interact_options.begin(); it != interact_options.end(); it++) {
        // if ((*it).size() > FRAME_INT_WIDTH - 5) {
        //     mvwaddstr(interact_window, h++, w, (*it).substr(0, FRAME_INT_WIDTH-2).c_str());
        //     std::string rem = (*it).substr(FRAME_INT_WIDTH - 2);
        //     while (rem.size() > 0) {
        //         if (rem.size() > FRAME_INT_WIDTH - 2) {
        //             mvwaddstr(interact_window, h++, w, rem.substr(0, FRAME_INT_WIDTH - 2).c_str());
        //             rem = rem.substr(FRAME_INT_WIDTH - 2);
        //         }
        //         else {
        //             mvwaddstr(interact_window, h++, w, rem.c_str());
        //             rem = "";
        //         }
        //     }
        // }
        mvwaddstr(interact_window, line++, indent * 2, (*it).c_str());
    }
    wnoutrefresh(interact_window);
}

void GameManager::drawMessageQueue() {
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    uint32_t line = 1, indent = 4;

    mvwaddstr(message_window, line++, indent, "Event Log:");
    if (messsage_queue.size() > 0) {
        while (messsage_queue.size() > FRAME_MSG_HEIGHT-3) {
            messsage_queue.pop();
        }

        std::queue<std::string> tmp_queue = std::queue<std::string>(messsage_queue);
        while (!tmp_queue.empty()) {
            mvwaddstr(message_window, line++, indent * 2, tmp_queue.front().c_str());
            tmp_queue.pop();
        }
    }

    wnoutrefresh(message_window);
}

void GameManager::drawAll() {
    wclear(map_window);
    wclear(interact_window);
    wclear(message_window);
    drawMessageQueue();
    drawInteractionMenu();
    drawMap();
    
    doupdate();
}

bool GameManager::handleMovement(std::shared_ptr<Entity> entity, Location offset) {
    if (entity == nullptr) {
        return false;
    }

    std::shared_ptr<RoomObject> room_object = findRoomByName(entity->getLocation().getRoomName())
                                                ->getRoomObject(entity->getLocation()+offset);

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

    for (auto it = object_list.begin(); it != object_list.end(); it++) {
        if ((**it).isDeleted()) {
            object_list.erase(it);
            break;
        }

        if ((**it).getLocation().getRoomName() == player->getLocation().getRoomName()) {
            if ((**it).getType() == Entity::EntityType::MOB) {
                Mob& mob = static_cast<Mob&>(**it);
                mob.think(object_list);
            }
        }
    }
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

std::shared_ptr<Room> GameManager::findRoomByName(std::string name) const {
    for (auto room : room_list) {
        if (room->getName() == name) {
            return room;
        }
    }
    
    return nullptr;
}