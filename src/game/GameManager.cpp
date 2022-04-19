#include "game/GameManager.hpp"

#include "entity/Mob.hpp"
#include "entity/Door.hpp"
#include "entity/Portal.hpp"

#include "inventory/Key.hpp"


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
    // Adaptive scaling.
    // Top right.
    FRAME_STAT_WIDTH = FRAME_WIDTH / 4;
    FRAME_STAT_HEIGHT = FRAME_HEIGHT / 5;
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

    wborder(map_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(status_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(interact_window, '|', '|', '-', '-', '+', '+', '+', '+');

    idcok(map_window, false);
    idcok(message_window, false);
    idcok(status_window, false);
    idcok(interact_window, false);

    wnoutrefresh(map_window);
    wnoutrefresh(message_window);
    wnoutrefresh(status_window);
    wnoutrefresh(interact_window);
    doupdate(); 
    //mnoecho();
}

void GameManager::createMap() {
    // Room initialization.
    std::shared_ptr<Room> lobby = std::make_shared<Room>(L"Lobby", L"Room Object", 15, 15);
    
    // Setting up a wall.
    for (size_t i = 0; i < 15; ++i) {
        if (i != 5)
            lobby->setRoomObject({5, i}, std::make_shared<RoomObject>(RoomObject::ObjectType::WALL));
    }

    std::shared_ptr<Room> mob_room_1 = std::make_shared<Room>(L"Room_1", L"Room Object", 20, 10);
    room_list.push_back(lobby);
    room_list.push_back(mob_room_1);

    // Generate entities (Mobs, Portals, NPCs).
    std::shared_ptr<Mob> mob = std::make_shared<Mob>(L"🤢", L"Slime", L"A normal silme", Location(lobby->getName(), 3, 14));
    std::shared_ptr<Key> key = std::make_shared<Key>(L"A old key", L"A key seems old.");
    mob->getInventory().addItem(key);
    object_list.push_back(mob);

    std::shared_ptr<Door> door = std::make_shared<Door>(L"Door", L"Door Object", Location(lobby->getName(), 5, 5), key->getName());
    object_list.push_back(door);

    std::shared_ptr<Portal> portal_1 = std::make_shared<Portal>(L"To Room 1", L"Portal Object", Location(lobby->getName(), 10, 10), Location(mob_room_1->getName(), 3, 3));
    object_list.push_back(portal_1);
}

void GameManager::createPlayer() {
    std::wstring name = L"Test Player";

    player = std::make_shared<Player>(name, L"Player", Location(room_list[0]->getName(), 2, 2));
}

void GameManager::handleInteraction() {
    // Draw interaction window.
    interact_options.clear();
    interact_options.push_back(L">> Movement (W: up, S:down, A:left, D: right");
    interact_options.push_back(L"c. Interact With Surroundings");
    interact_options.push_back(L"f. Inspect Objects");
    interact_options.push_back(L"i. Use items in inventory");
    drawAll();

    // Loop until we get a valid input.
    uint32_t ch = 0;
    while (ch != 'w' && ch != 's' && ch != 'a' && ch != 'd' && ch != 'c' && ch != 'i' && ch != 'f') {
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

            if(handleMovement(player, Location(y, x))) {
                pushActionMessage(L"You moved.");
            } else {
                pushActionMessage(L"You can't move there.");
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
                pushActionMessage(L"There is nothing to interact with.");
                drawInteractionMenu();
                return;
            }

            interact_options.clear();
            for (size_t i = 0; i < assessible.size(); i++) {
                std::wstring action;
                switch( assessible[i]->getType() ) {
                    case Entity::EntityType::CHEST:
                        action = L"🫳Loot";
                        break;
                    case Entity::EntityType::DOOR:
                        action = L"🔓Open";
                        break;
                    case Entity::EntityType::ITEM:
                        action = L"🫴Pick up";
                        break;
                    case Entity::EntityType::MOB:
                        action = L"⚔️Attack";
                        break;
                    case Entity::EntityType::NPC:
                        action = L"🗣Talk";
                        break;
                    case Entity::EntityType::PORTAL:
                        action = L"💡Teleport";
                        break;
                    case Entity::EntityType::SIGN:
                        action = L"🔍Inspect";
                        break;
                    default:
                        action = L"❌Broken la";
                        break;
                }
                interact_options.push_back(std::to_wstring(i) + L". " + action + L" " + assessible[i]->getName());
            }
            interact_options.push_back(L"q. Leave interact");
            drawInteractionMenu();

            ch = mvwgetch(interact_window, 1, 1);
            if (ch - '0' < assessible.size() && ch - '0' >= 0) {
                assessible[ch - '0']->interact(*player);
                return;
            }
            else if (ch == 'q') {
                pushActionMessage(L"You leave the interact menu");
                return;
            }
            pushActionMessage(L"Invalid option...");
            return;

        }
        else if (ch == 'f') {
            interact_options.clear();
            std::vector<std::shared_ptr<Entity>> assessible;
            for (size_t i = 0; i < object_list.size(); i++) {
                if (player->getLocation().distance(object_list[i]->getLocation()) <= 1.5) {
                    assessible.push_back(object_list[i]);
                    interact_options.push_back(std::to_wstring(assessible.size()-1) + L". Inspect " + object_list[i]->getName());
                }
            }
            if (assessible.size() < 1) {
                interact_options.clear();
                pushActionMessage(L"There is nothing to inspect.");
                drawInteractionMenu();
                return;
            }
            drawInteractionMenu();

            ch = mvwgetch(interact_window, 1, 1);
            if (ch - '0' < assessible.size() && ch - '0' >= 0) {
                pushActionMessage(L"You inspect " + assessible[ch - '0']->getName());
                pushActionMessage(L"    > " + assessible[ch - '0']->getDescription());
                return;
            }
            else if (ch == 'q') {
                pushActionMessage(L"You leave the Inspection menu");
                return;
            }
            pushActionMessage(L"Invalid option...");
            return;

        }
        else if (ch == 'i') {
            interact_options.clear();
            std::vector<std::shared_ptr<InventoryItem>> assessible;
            for (size_t i = 0; i < player->getInventory().getItems().size(); i++) {
                assessible.push_back(player->getInventory().getItems()[i]);
                interact_options.push_back(
                    std::to_wstring(assessible.size() - 1) + L". " + player->getInventory().getItems().at(i)->getName());
            }
            if (assessible.size() < 1) {
                interact_options.clear();
                pushActionMessage(L"Nothing in your inventory.");
                drawInteractionMenu();
                return;
            }
            drawInteractionMenu();

            ch = mvwgetch(interact_window, 1, 1);
            if (ch - '0' < assessible.size() && ch - '0' >= 0) {
                pushActionMessage(L"You use " + assessible[ch - '0']->getName());
                assessible[ch - '0']->use(*player);
                return;
            }
            else if (ch == 'q') {
                pushActionMessage(L"You leave the Inventory menu");
                return;
            }
            pushActionMessage(L"Invalid option...");
            return;

        }

        return;
    }
}  

void GameManager::drawMap() {
    std::vector<std::vector<std::wstring>>frame_map_data = std::vector<std::vector<std::wstring>>(GameManager::FRAME_MAP_HEIGHT, std::vector<std::wstring>(GameManager::FRAME_MAP_WIDTH, L" "));

    std::shared_ptr<Room> room = findRoomByName(player->getLocation().getRoomName());
    if (room == nullptr) {
        pushActionMessage(L"[ERROR] [GameManager::drawMap]: Room not found.");
        return;
    }

    // Draw RoomObject.
    int32_t lx = room->getMaxWidth() / 2 - FRAME_MAP_WIDTH / 2 - 1;
    int32_t rx = room->getMaxWidth() / 2 + FRAME_MAP_WIDTH / 2;
    int32_t ly = room->getMaxHeight() / 2 - FRAME_MAP_HEIGHT / 2 - 1;
    int32_t ry = room->getMaxHeight() / 2 + FRAME_MAP_HEIGHT / 2;
    int32_t max_y = room->getMaxHeight();
    int32_t max_x = room->getMaxWidth();

    for (auto i = ly, fi = 1; i < ry && fi < FRAME_MAP_HEIGHT - 1; ++i, ++fi) {
        for (auto j = lx, fj = 1; j < rx && fj < FRAME_MAP_WIDTH - 1; ++j, ++fj) {
            // If we trying to draw a frame that is out of the room, draw nothing.
            if (i < 0 || j < 0 || i >= max_y || j >= max_x) {
                frame_map_data[fi][fj] = L"";
            } else {
                frame_map_data[fi][fj] = room->getRoomObject({(uint32_t)i, (uint32_t)j})->getIcon();
            }
        }
    }

    // Draw Player.
    frame_map_data[player->getLocation().getY() - ly + 1][player->getLocation().getX() - lx + 1] = player->getIcon();

    // Draw other objects.
    for (auto it = object_list.begin(); it != object_list.end(); it++) {
        // Put object icon into frame_map_data if it is in the same room with player.
        if ((**it).getLocation().getRoomName() == player->getLocation().getRoomName()) {
            frame_map_data[(**it).getLocation().getY() - ly + 1][(**it).getLocation().getX() - lx + 1] = (**it).getIcon();
        }
    }

    
    wclear(map_window);
    wborder(map_window, '|', '|', '-', '-', '+', '+', '+', '+');
    // Update window.
    for (uint32_t i = 1; i < FRAME_MAP_HEIGHT-1; ++i) {
        for (uint32_t j = 1; j < FRAME_MAP_WIDTH-1; ++j) {
            mvwaddwstr(map_window, i, j, frame_map_data[i][j].c_str());
        }
    }
    
    wnoutrefresh(map_window);

}

void GameManager::drawInteractionMenu() {
    werase(interact_window);
    wborder(interact_window, '|', '|', '-', '-', '+', '+', '+', '+');

    uint32_t line = 1, indent = 4;
    mvwaddstr(interact_window, line++, indent, "Actions:");
    for (auto it = interact_options.begin(); it != interact_options.end(); it++) {
        mvwaddwstr(interact_window, line++, indent * 2, (*it).c_str());
    }
    wnoutrefresh(interact_window);
}

void GameManager::drawMessageQueue() {
    werase(message_window);
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    uint32_t line = 1, indent = 4;

    mvwaddstr(message_window, line++, indent, "Event Log:");
    if (messsage_queue.size() > 0) {
        while (messsage_queue.size() > FRAME_MSG_HEIGHT-3) {
            messsage_queue.pop();
        }

        std::queue<std::wstring> tmp_queue = std::queue<std::wstring>(messsage_queue);
        while (!tmp_queue.empty()) {
            mvwaddwstr(message_window, line++, indent * 2, tmp_queue.front().c_str());
            tmp_queue.pop();
        }
    }

    wnoutrefresh(message_window);
}

void GameManager::drawPlayerStatus() {
    werase(status_window);

    wborder(status_window, '|', '|', '-', '-', '+', '+', '+', '+');
    uint32_t line = 1, indent = 4;

    mvwaddwstr(status_window, line++, indent, L"Player Status:");
    mvwaddwstr(status_window, line++, indent * 2, std::wstring(L"❤️ Health: " + std::to_wstring(player->getHealth()) + L"/" + std::to_wstring(player->getMaxHealth())).c_str());
    mvwaddwstr(status_window, line++, indent * 2, std::wstring(L"🛡 Defense: " + std::to_wstring(player->getDefense())).c_str());
    mvwaddwstr(status_window, line++, indent * 2, std::wstring(L"🍀 Luck: " + std::to_wstring(player->getLuck())).c_str());

    wnoutrefresh(status_window);
}

void GameManager::drawAll() {
    drawMap();
    drawInteractionMenu();
    drawMessageQueue();
    drawPlayerStatus();
    doupdate();
}

bool GameManager::handleMovement(std::shared_ptr<Entity> entity, Location offset) {
    if (entity == nullptr) {
        return false;
    }

    // Checking object collidsion.
    for (auto it = object_list.begin(); it != object_list.end(); it++) {
        if ((**it).getLocation() == entity->getLocation() + offset) {
            if ((**it).getType() == Entity::EntityType::DOOR) {
                return false;
            }
        }
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

void GameManager::pushActionMessage(std::wstring message) {
    messsage_queue.push(message);
}

std::shared_ptr<Room> GameManager::findRoomByName(std::wstring name) const {
    for (auto room : room_list) {
        if (room->getName() == name) {
            return room;
        }
    }
    
    return nullptr;
}

void GameManager::addEntity(std::shared_ptr<Entity> entity) {
    object_list.push_back(entity);
}