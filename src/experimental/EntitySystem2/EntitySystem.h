#ifndef HAMMER_ENGINE_ENTITYSYSTEM__H_
#define HAMMER_ENGINE_ENTITYSYSTEM__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

class AbstractTrait;
class BehaviorFunctor;
class TraitFactory;
class MemoryPool;
class Entity;

enum EntityState
{
    Running = 0,
    Paused
};

class EntitySystem
{
public:
    virtual ~EntitySystem () {}

    // Entity API
    virtual Entity&         createEntity        () = 0;
    virtual Entity&         getEntityFromTrait  (const AbstractTrait* trait) = 0;
    virtual Entity&         getEntity           (unsigned int entity) = 0;
    virtual void            destroyEntity       (const Entity&)=0; // Queued
    virtual EntityState     getState            (const Entity&)=0;
    virtual void            setState            (const Entity&, const EntityState&)=0; // Queued

    // Trait API
    virtual void            registerTrait       (unsigned int trait, TraitFactory* factory) = 0;
    virtual AbstractTrait*  getTrait            (unsigned int entity, unsigned int trait)   = 0;
    virtual void            addTrait            (unsigned int entity, unsigned int trait)   = 0; // Queued
    virtual void            removeTrait         (unsigned int entity, unsigned int trait)   = 0; // Queued

    // Behavior API
    virtual void            registerBehavior    (unsigned int trait, BehaviorFunctor* functor) = 0;

    // Miscillaneus
//    virtual MemoryPool*     createMemoryPool    (unsigned int elementSize) = 0;
};

#endif // HAMMER_ENGINE_ENTITYSYSTEM__H_
