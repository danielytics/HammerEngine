#ifndef HAMMER_ENGINE_ENTITYSYSTEM__H_
#define HAMMER_ENGINE_ENTITYSYSTEM__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

class Trait;
class BehaviorFunctor;

class EntitySystem
{
public:
    // Trait API
    virtual Trait* getTrait  (unsigned int entity, unsigned int trait) = 0;
    virtual void addTrait    (unsigned int entity, unsigned int trait) = 0;
    virtual void removeTrait (unsigned int entity, unsigned int trait) = 0;

    // Behavior API
    virtual void registerBehavior (unsigned int trait, const BehaviorFunctor& functor)=0;
};

#endif // ENTITYSYSTEM_H
