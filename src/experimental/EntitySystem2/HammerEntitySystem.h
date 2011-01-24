#ifndef HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_
#define HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_

#include "EntitySystem.h"
#include "ReadOnlyEntitySystem.h"
#include "UnalignedMemoryPool.h"
#include "Entity.h"

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_vector.h>

class TraitFactory;
class BehaviorFunctor;
class EventDispatcher;
class HammerEventDispatcher;

class HammerEntitySystem : public EntitySystem
{
private:
    CreateMemoryPool<UnalignedMemoryPool, MemoryFeatures::DefaultDynamicPoolFeatures, Entity>::Type entityPool;

    tbb::concurrent_unordered_map<unsigned int, TraitFactory*> traitRegistrar;
    tbb::concurrent_unordered_map<const AbstractTrait::Type, Entity*> traitToEntityMap;
    tbb::concurrent_vector<Entity*> entityList;
    tbb::concurrent_vector<std::pair<unsigned int, BehaviorFunctor*> > behaviors;

    const ReadOnlyEntitySystem* const readOnlySystem;
    HammerEventDispatcher* const eventDispatcher;
    Entity* invalidEntity;

public:
    HammerEntitySystem ();

    virtual ~HammerEntitySystem ();

    // Entity API
    Entity& createEntity ();
    Entity& getEntityFromTrait (const AbstractTrait::Type trait) const;
    Entity& getEntity (unsigned int entity) const;
    void destroyEntity (const unsigned int entity);
    EntityState getState (const unsigned int entity) const;
    void setState (const unsigned int entity, const EntityState& state);

    const ReadOnlyEntity getReadOnlyEntity (const unsigned int entity) const;

    // Trait API
    void registerTrait (unsigned int trait, TraitFactory* factory);
    AbstractTrait::Type getTrait (unsigned int entity, unsigned int trait) const;
    void addTrait (unsigned int entity, unsigned int trait);
    void removeTrait (unsigned int entity, unsigned int trait);

    // Behavior API
    void registerBehavior (unsigned int trait, BehaviorFunctor* functor);

    // Miscillaneus
//    MemoryPool* createMemoryPool (unsigned int elementSize);

    // Private API
    void updateBehavior ();
    EventDispatcher* getEventDispatcher ();
};

#endif // HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_
