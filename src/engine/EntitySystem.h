#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <vector>

#include <HammerEngine/EntitySystem/EntitySystem.h>
#include <HammerEngine/EntitySystem/Trait.h>
#include <HammerEngine/EntitySystem/Entity.h>
#include <HammerEngine/Resources/Handle.h>

#include "Resource/Resource.h"

class Image : public Resource
{
public:
    static const unsigned int handle_type = ResourceManager::registerResource();
};

class Position : public TraitBase<Position>
{
public:
    static const unsigned int id = EntitySystem::registerTrait();

    Position& operator= (const Vector& vec)
    {
        vector = vec;
        return *this;
    }
};

class Movement : public TraitBase<Movement>
{
public:

    static const unsigned int id = EntitySystem::registerTrait();
};

class Drawable : public TraitBase<Drawable>
{
public:

    const Handle img () const
    {
        return handle();
    }

    Drawable& operator= (Handle h)
    {
        HANDLE_GUARD(h, Image);
        handle() = h;
    }

    static const unsigned int id = EntitySystem::registerTrait();
};

class Message {};

void do_position_system (const Trait& inTrait1, const Trait& inTrait2, Trait& outTrait, const std::vector<Message>& inbox, const std::vector<Message>& outbox)
{
    // Process messages
    for (std::vector<Message>::iterator i = inbox.begin(); i != inbox.end(); ++i)
    {
        // Message pass through
        outbox.push_back(*i);
    }

    const Position& position = static_cast<const Position>(inTrait1);
    const Movement& movement = static_cast<const Movement>(inTrait2);
    Position& newPosition = static_cast<Position>(outTrait);

    newPosition = position() + (movement.heading() * movement.speed());
}

void do_position_behavior (const Position& position, const Movement& movement, Position& out)
{
    out = position() + (movement.heading() * movement.speed());
}

#include <HammerEngine/Module.h>

int main ()
{
    EntitySystem entitySystem;
    Hammer::Engine* engine = 0;

    Entity player = entitySystem.createEntity()
                        .addTrait<Position>()
                        .addTrait<Drawable>();

    Hammer::BehaviorBuilder builder(engine);
    builder.registerBehavior(do_position_behavior);

    player<Position>() = Vector(0.0f, 0.0f, 0.0f);
}

#endif // ENTITYSYSTEM_H
