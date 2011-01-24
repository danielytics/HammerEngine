
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"
#include "Event.h"

#include "Collidable.h"

void do_collidable (const Collidable& collidable, const Position& position)
{
    /*
     * event("<attribute-name>") (optional)
     * Contains the events payload.
     * EventAttribute, can hold numbers, strings and Traits.
     *
     * event.type (optionsl)
     * String identifier describing the type of event
     *
     * event.mailbox (optional)
     * String identifier describing events destination
     *
     */
    {
        SendEvent event("CheckCollision"); // Receiver filters type, or receiver is duck typed
        event("position") = position;
    }
    {
        SendEvent event("", "NorseGame/Collisions"); // MessageBus filters sender
        event("position") = position;
    }
}



void CollidableUtils::install (TraitBuilder* tb, BehaviorBuilder* bb)
{
    tb->registerTrait<MemoryFeatures::DefaultDynamicPoolFeatures, Collidable>();
    bb->registerBehavior(do_collidable);
}

std::ostream& operator<< (std::ostream& os, const Collidable& input)
{
    os << "<Collidable>";
    return os;
}
