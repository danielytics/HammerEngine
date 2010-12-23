#ifndef HAMMER_ENGINE_ENTITY__H_
#define HAMMER_ENGINE_ENTITY__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "EntitySystem/EntitySystem.h"

class Entity
{
private:
    EntitySystem& owner;

public:
    Entity (EntitySystem& o, unsigned int ident) : owner(o), id(ident) {}

    const unsigned int id;

    // Convenience functions for accessing an entities traits

    template <class T> inline T operator() () const
    {
        return *static_cast<T*>(owner.getTrait(id, T::id));
    }

    template <class T> inline Entity& addTrait () const
    {
        owner.addTrait(id, T::id);
        return *this;
    }

    template <class T> inline Entity& removeTrait () const
    {
        owner.removeTrait(id, T::id);
        return *this;
    }
};

#endif // ENTITY_H
