
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"

#include "Collidable.h"

//struct Event {};

//class EventHandler
//{
//public:
//    virtual void handle (const std::vector<Event>& events)=0;
//};

//class CollisionHandler : public EventHandler
//{
//public:
//    void handle (std::vector<Event>& events)
//    {
//        // events is a list of all CollisionCheckEvents (that is, all collidable entities)
//        // which must be checked for collisions.
//        // First we should sort them by location so that we dont have to check every event against every other event.
//        // Then we check close events against each other for collisions.
//        // For each collision that occurs, we modify the entities movement trait (if it has one, if not then the collision does not effect that entity - ie its static).
//    }
//};


void CollidableUtils::install (TraitBuilder* tb, BehaviorBuilder* bb)
{
    tb->registerTrait<MemoryFeatures::DefaultDynamicPoolFeatures, Collidable>();
}

std::ostream& operator<< (std::ostream& os, const Collidable& input)
{
    os << "<Collidable>";
    return os;
}
