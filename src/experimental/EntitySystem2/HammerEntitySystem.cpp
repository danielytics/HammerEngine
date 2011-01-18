
#include <iostream>

#include "HammerEntitySystem.h"
#include "TraitBuilder.h"
#include "BehaviorFunctor.h"

#include "DebugTools.h"

#include <iostream>

struct EntityConstructor
{
    EntitySystem* thisPtr;
    unsigned int id;
    inline Entity* construct (char* buffer)
    {
        return new (buffer) Entity(*thisPtr, id);
    }
};

HammerEntitySystem::HammerEntitySystem ()
{
    invalidEntity = new Entity(*this, (unsigned int)-1);
}

HammerEntitySystem::~HammerEntitySystem ()
{
    for (std::vector<Entity*>::iterator iter = entityList.begin(); iter != entityList.end(); ++iter)
    {
        entityPool.release(*iter);
    }
    // TODO: delete traits
}

// Entity API
Entity& HammerEntitySystem::createEntity ()
{
    EntityConstructor ctor;
    ctor.thisPtr = this;
    ctor.id = entityList.size();
//    Entity* entity = new Entity(*this, entityList.size()); // TODO: Memory pool
    Entity* entity = entityPool.request<EntityConstructor>(ctor);
    entityList.push_back(entity);
    return *deref(entity);
}

Entity& HammerEntitySystem::getEntityFromTrait  (const AbstractTrait* trait)
{
    std::unordered_map<const AbstractTrait*, Entity*>::iterator iter = traitToEntityMap.find(trait);
    if (iter != traitToEntityMap.end())
    {
        return *deref((deref_iter(iter, traitToEntityMap).second));
    }
    return *deref(invalidEntity);
}

Entity& HammerEntitySystem::getEntity (unsigned int entity)
{
    return (entity < entityList.size()) ? *deref(entityList[entity]) : *deref(invalidEntity);
}

// TODO: Queue until next behavior update
void HammerEntitySystem::destroyEntity (const Entity& entity)
{
    Entity* e = &getEntity(entity.id);
    if (e->valid)
    {
        entityList[entity.id] = invalidEntity;
        // TODO: delete traits
        delete e;
    }
}

EntityState HammerEntitySystem::getState (const Entity& entity)
{
    return Running;
}

// TODO: Queue until next behavior update
void HammerEntitySystem::setState (const Entity& entity, const EntityState& state)
{

}

// Trait API
void HammerEntitySystem::registerTrait (unsigned int trait, TraitFactory* factory)
{
    traitRegistrar[trait] = factory;
}

AbstractTrait* HammerEntitySystem::getTrait (unsigned int entity, unsigned int trait)
{
    std::unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(trait);
    if (iter != traitRegistrar.end())
    {
        TraitFactory* factory = deref_iter(iter, traitRegistrar).second;
        if (factory != 0)
        {
            return deref(factory)->lookup(entity);
        }
    }
    return 0;
}

// TODO: Queue until next behavior update
void HammerEntitySystem::addTrait (unsigned int entity, unsigned int trait)
{
    std::unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(trait);
    if (iter != traitRegistrar.end())
    {
        TraitFactory* factory = deref_iter(iter, traitRegistrar).second;
        if (factory != 0)
        {
            traitToEntityMap[deref(factory)->create(entity)] = &getEntity(entity);
        }
    }
}

// TODO: Queue until next behavior update
void HammerEntitySystem::removeTrait (unsigned int entity, unsigned int trait)
{
    std::unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(trait);
    if (iter != traitRegistrar.end())
    {
        TraitFactory* factory = deref_iter(iter, traitRegistrar).second;
        if (factory != 0)
        {
            deref(factory)->destroy(entity);
        }
    }
}

// Behavior API
void HammerEntitySystem::registerBehavior (unsigned int trait, BehaviorFunctor* functor)
{
    behaviors.push_back(std::pair<unsigned int, BehaviorFunctor*>(trait, functor));
}

/**
  * Execute each behavior.
  * This is what makes the entity system "work" and is part of the private framework API (that is, code
  * written in terms of entities, traits and behaviors do not ever use this API, instead it is called for them
  * behind the scenes).
  */
void HammerEntitySystem::updateBehavior ()
{
    for (unsigned int i=0; i < behaviors.size(); ++i)
    {
        unsigned int traitId = behaviors[i].first;
        std::unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(traitId);
        if (iter != traitRegistrar.end())
        {
            TraitFactory* factory = deref_iter(iter, traitRegistrar).second;
            if (factory != 0)
            {
                std::vector<unsigned int> entities;
                deref(factory)->getEntities(entities);

                std::vector<unsigned int>::iterator it = entities.begin();
                Entity* entity = 0;
                // Process each entity
                while (it != entities.end())
                {
                    // Get the entity
                    entity = &getEntity(deref_iter(it, entities));
                    // Process current entity
                    (*(behaviors[i].second))(*deref(entity));
                    // Advance to next entity
                    ++it;
                }
            }
        }
    }
}
;
