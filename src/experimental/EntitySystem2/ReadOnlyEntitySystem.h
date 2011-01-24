#ifndef READONLYENTITYSYSTEM_H
#define READONLYENTITYSYSTEM_H

/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "Trait.h"
#include "EntityState.h"

class BehaviorFunctor;
class TraitFactory;
class MemoryPool;
class ReadOnlyEntity;

class ReadOnlyEntitySystem
{
public:
    virtual ~ReadOnlyEntitySystem () {}

    // Entity system API
    virtual const ReadOnlyEntity      getEntityFromTrait  (const AbstractTrait::Type trait) const = 0;
    virtual const ReadOnlyEntity      getEntity           (unsigned int entity) const = 0;
    virtual const EntityState         getState            (const unsigned int entity) const = 0;
    virtual const AbstractTrait::Type getTrait            (unsigned int entity, unsigned int trait) const = 0;
};

#endif // READONLYENTITYSYSTEM_H
