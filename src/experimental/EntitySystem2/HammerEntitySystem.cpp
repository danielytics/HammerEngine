
#include <iostream>
#include <vector>

#include <tbb/parallel_for.h>

#include "HammerEntitySystem.h"
#include "TraitBuilder.h"
#include "BehaviorFunctor.h"

#include "DebugTools.h"

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
    for (tbb::concurrent_vector<Entity*>::iterator iter = entityList.begin(); iter != entityList.end(); ++iter)
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
    Entity* entity = entityPool.request<EntityConstructor>(ctor);
    entityList.push_back(entity);
    return *deref(entity);
}

Entity& HammerEntitySystem::getEntityFromTrait  (const AbstractTrait::Type trait)
{
    tbb::concurrent_unordered_map<const AbstractTrait::Type, Entity*>::iterator iter = traitToEntityMap.find(trait);
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

AbstractTrait::Type HammerEntitySystem::getTrait (unsigned int entity, unsigned int trait)
{
    tbb::concurrent_unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(trait);
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
    tbb::concurrent_unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(trait);
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
    tbb::concurrent_unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(trait);
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


class ProcessEntities
{
    HammerEntitySystem& m_engine;
    std::vector<unsigned int>& m_entities;
    BehaviorFunctor* m_behavior;

public:
    ProcessEntities (HammerEntitySystem& ngin, std::vector<unsigned int>& e, BehaviorFunctor*& b)
        : m_engine(ngin)
        , m_entities(e)
        , m_behavior(b)
    {
    }

    void operator() (const tbb::blocked_range<size_t>& r) const
    {
        HammerEntitySystem& engine = m_engine;
        std::vector<unsigned int>& entities = m_entities;
        BehaviorFunctor* behavior = m_behavior;

        // Process each behavior.
        for(std::size_t i = r.begin(); i != r.end(); ++i)
        {
            // Get the entity
            Entity* entity = &engine.getEntity(entities[i]);
            // Process current entity
            (*behavior)(*deref(entity));
        }
    }
};


class ProcessBehaviors
{
    typedef tbb::concurrent_vector<std::pair<unsigned int, BehaviorFunctor*> > Behaviors;
    typedef tbb::concurrent_unordered_map<unsigned int, TraitFactory*> TraitRegistrar;

    HammerEntitySystem& m_engine;
    Behaviors& m_behaviors;
    TraitRegistrar& m_traitRegistrar;

public:
    ProcessBehaviors (HammerEntitySystem* ngin, Behaviors& b, TraitRegistrar& t)
        : m_engine(*ngin)
        , m_behaviors(b)
        , m_traitRegistrar(t)
    {
    }

    void operator() (const tbb::blocked_range<size_t>& r) const
    {
        Behaviors& behaviors = m_behaviors;
        TraitRegistrar& traitRegistrar = m_traitRegistrar;
        HammerEntitySystem& engine = m_engine;

        // Process each behavior.
        for(std::size_t i = r.begin(); i != r.end(); ++i)
        {
            //unsigned int traitId = deref_iter(behavior_iter, behaviors).first;
            std::pair<unsigned int, BehaviorFunctor*>  pair = behaviors[i];
            unsigned int traitId = pair.first;


            // Get trait factory for behvaiors main trait
            TraitRegistrar::iterator iter = traitRegistrar.find(traitId);
            if (iter != traitRegistrar.end())
            {
                TraitFactory* factory = deref_iter(iter, traitRegistrar).second;
                if (factory != 0)
                {
                    // Get vector of entities for current trait
                    std::vector<unsigned int> entities;
                    deref(factory)->getEntities(entities);

                    // Iterate through and process the entities
                    tbb::parallel_for(tbb::blocked_range<size_t>(0, entities.size()), ProcessEntities(engine, entities, pair.second));
                }
            }
        }
    }
};

/**
  * Execute each behavior.
  * This is what makes the entity system "work" and is part of the private framework API (that is, code
  * written in terms of entities, traits and behaviors do not ever use this API, instead it is called for them
  * behind the scenes).
  */
void HammerEntitySystem::updateBehavior ()
{
#ifndef PROCESS_SERIAL /* Parallel code */

    tbb::parallel_for(tbb::blocked_range<size_t>(0, behaviors.size()), ProcessBehaviors(this, behaviors, traitRegistrar));

#else /* Serial code */

    // Iterate through behaviors
    tbb::concurrent_vector<std::pair<unsigned int, BehaviorFunctor*> >::iterator behavior_iter = behaviors.begin();

    // PARALLEL
    for (; behavior_iter != behaviors.end(); ++behavior_iter)
    {
        unsigned int traitId = deref_iter(behavior_iter, behaviors).first;

        // Get trait factory for behvaiors main trait
        tbb::concurrent_unordered_map<unsigned int, TraitFactory*>::iterator iter = traitRegistrar.find(traitId);
        if (iter != traitRegistrar.end())
        {
            TraitFactory* factory = deref_iter(iter, traitRegistrar).second;
            if (factory != 0)
            {
                // Get vector of entities for current trait
                std::vector<unsigned int> entities;
                deref(factory)->getEntities(entities);

                // Iterate through the entities
                std::vector<unsigned int>::iterator it = entities.begin();
                Entity* entity = 0;

                // Process each entity
                // PARALLEL
                for (; it != entities.end(); ++it)
                {
                    // Get the entity
                    entity = &getEntity(deref_iter(it, entities));
                    // Process current entity
                    (*(deref_iter(behavior_iter, behaviors).second))(*deref(entity));
                }
            }
        }
    }
#endif
}

