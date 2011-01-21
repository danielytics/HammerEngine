#ifndef HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_
#define HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_

#include "EntitySystem.h"
#include "UnalignedMemoryPool.h"
#include "Entity.h"

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_vector.h>

class TraitFactory;
class BehaviorFunctor;

class HammerEntitySystem : public EntitySystem
{
private:
    CreateMemoryPool<UnalignedMemoryPool, MemoryFeatures::DefaultDynamicPoolFeatures, Entity>::Type entityPool;

    tbb::concurrent_unordered_map<unsigned int, TraitFactory*> traitRegistrar;
    tbb::concurrent_unordered_map<const AbstractTrait::Type, Entity*> traitToEntityMap;
    tbb::concurrent_vector<Entity*> entityList;
    tbb::concurrent_vector<std::pair<unsigned int, BehaviorFunctor*> > behaviors;

    Entity* invalidEntity;

public:
    HammerEntitySystem ();

    virtual ~HammerEntitySystem ();

    // Entity API
    Entity& createEntity ();
    Entity& getEntityFromTrait (const AbstractTrait::Type trait);
    Entity& getEntity (unsigned int entity);
    void destroyEntity (const Entity&);
    EntityState getState (const Entity& entity);
    void setState (const Entity& entity, const EntityState& state);

    // Trait API
    void registerTrait (unsigned int trait, TraitFactory* factory);
    AbstractTrait::Type getTrait (unsigned int entity, unsigned int trait);
    void addTrait (unsigned int entity, unsigned int trait);
    void removeTrait (unsigned int entity, unsigned int trait);

    // Behavior API
    void registerBehavior (unsigned int trait, BehaviorFunctor* functor);

    // Miscillaneus
//    MemoryPool* createMemoryPool (unsigned int elementSize);

    // Private API
    void updateBehavior ();
};

#endif // HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_
