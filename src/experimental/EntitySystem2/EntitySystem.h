#ifndef HAMMER_ENGINE_ENTITYSYSTEM__H_
#define HAMMER_ENGINE_ENTITYSYSTEM__H_
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
class Entity;
class ReadOnlyEntity;

class EntitySystem
{
public:
    virtual ~EntitySystem () {}

    // Entity API
    virtual Entity&         createEntity        () = 0;
    virtual Entity&         getEntityFromTrait  (const AbstractTrait::Type trait) const = 0;
    virtual Entity&         getEntity           (unsigned int entity) const = 0;
    virtual void            destroyEntity       (const unsigned int entity) = 0; // Queued
    virtual EntityState     getState            (const unsigned int entity) const = 0;
    virtual void            setState            (const unsigned int entity, const EntityState&)=0; // Queued

    virtual const ReadOnlyEntity getReadOnlyEntity (const unsigned int entity) const = 0;

    // Trait API
    virtual void            registerTrait       (unsigned int trait, TraitFactory* factory) = 0;
    virtual AbstractTrait::Type  getTrait       (unsigned int entity, unsigned int trait) const = 0;
    virtual void            addTrait            (unsigned int entity, unsigned int trait)   = 0; // Queued
    virtual void            removeTrait         (unsigned int entity, unsigned int trait)   = 0; // Queued

    // Behavior API
    virtual void            registerBehavior    (unsigned int trait, BehaviorFunctor* functor) = 0;
};

#endif // HAMMER_ENGINE_ENTITYSYSTEM__H_
