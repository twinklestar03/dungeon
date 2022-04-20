#include "entity/NPC.hpp"
#include "game/GameManager.hpp"

#include "inventory/Potion.hpp"


NPC::NPC(std::wstring name, std::wstring description, Location location)
    : Entity(EntityType::NPC, name, description, location) {
    this->script.insert({L"GREETING", L"Hello there!"});
    this->script.insert({L"LEAVING", L"Goodbye!"});
    this->script.insert({L"ASK_PURCHASE", L"What do you want to get?"});
    this->script.insert({L"COMPLETE_PURCHASE", L"You got the item in your inventory."});

    this->product.push_back(std::make_shared<Potion>(Potion::PotionType::HEAL, L"Potion of Healing", L"A potion that restores health", 1, 10));
}

NPC::~NPC() {
    //GameManager::getInstance().pushActionMessage(L"DEBUG: NPC (" + this->getName() + L") is being deleted.");
}

bool NPC::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        auto player = dynamic_cast<Player*>(&entity);
        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] (NPC::interact): Player object cannot be referenced.");
            return false;
        }

        GameManager::getInstance().clearInteractOption();
        GameManager::getInstance().addInteractOption(L"b. Get items");
        GameManager::getInstance().addInteractOption(L"q. Quit");
        GameManager::getInstance().pushActionMessage(script.at(L"GREETING"));
        GameManager::getInstance().drawMessageQueue();
        GameManager::getInstance().drawInteractionMenu();

        char ch = GameManager::getInstance().getInput({'b', 'q'});
        if (ch != '\0') {
            switch (ch) {
                case 'b':
                    GameManager::getInstance().pushActionMessage(script.at(L"ASK_PURCHASE"));

                    GameManager::getInstance().clearInteractOption();
                    for (size_t i = 0; i < product.size(); i++) {
                        GameManager::getInstance().addInteractOption(
                            std::to_wstring(i) +
                            L". " +
                            product[i]->getName() +
                            L"(" +
                            std::to_wstring(purchase_table[product[i]->getName()]) +
                            L")"
                        );
                    }
                    GameManager::getInstance().addInteractOption(L"q. Quit");
                    GameManager::getInstance().drawInteractionMenu();
                    GameManager::getInstance().drawMessageQueue();

                    ch = GameManager::getInstance().getInput({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'q'});
                    while (ch == '\0') {
                        GameManager::getInstance().pushActionMessage(L"Invalid input.");
                        GameManager::getInstance().drawMessageQueue();
                        ch = GameManager::getInstance().getInput({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'q'});
                    }
                    
                    if (ch == 'q') {
                        GameManager::getInstance().pushActionMessage(script.at(L"LEAVING"));
                        GameManager::getInstance().drawMessageQueue();
                        return true;
                    }
                    else {
                        // TODO: Check if player has enough money.
                        player->getInventory().addItem(product[ch - '0']);
                        GameManager::getInstance().pushActionMessage(script.at(L"LEAVING"));
                        GameManager::getInstance().drawMessageQueue();
                        return true;
                    }

                    break;
                case 'q': 
                    GameManager::getInstance().pushActionMessage(script.at(L"LEAVING"));
                    break;
            }
        }
        
    }
    return false;
}