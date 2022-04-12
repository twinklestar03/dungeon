#pragma once
#include "entity/Entity.hpp"


class Event {
public:
    enum class EventType {
        ENTITY_MOVE,
        ENTITY_SPAWN,
        ENTITY_ATTACK,
        ENTITY_KILLED,
        ENTITY_DEATH,
        PORTAL_TRIGGER,
    };

    Event(EventType event_type, Entity executor, Entity target);
    ~Event() = default;

    EventType getEventType();
    Entity getExecutor();
    Entity getTarget();

    void setEventType(EventType event_type);
    void setExecutor(Entity executor);
    void setTarget(Entity target);

private:
    EventType event_type;
    Entity executor;
    Entity target;
};
