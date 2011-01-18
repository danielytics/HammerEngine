#ifndef HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_
#define HAMMER_ENGINE_HAMMERENTITYSYSTEM__H_

#include <vector>
#include <unordered_map>

#include "EntitySystem.h"

class TraitFactory;
class BehaviorFunctor;

class HammerEntitySystem : public EntitySystem
{
private:
    unsigned int next_id;

    std::unordered_map<unsigned int, TraitFactory*> traitRegistrar;
    std::unordered_map<const AbstractTrait*, Entity*> traitToEntityMap;
    std::vector<Entity*> entityList;
    std::vector<std::pair<unsigned int, BehaviorFunctor*> > behaviors;

    Entity* invalidEntity;

public:
    HammerEntitySystem ();

    virtual ~HammerEntitySystem ();

    // Entity API
    Entity& createEntity ();
    Entity& getEntityFromTrait (const AbstractTrait* trait);
    Entity& getEntity (unsigned int entity);
    void destroyEntity (const Entity&);
    EntityState getState (const Entity& entity);
    void setState (const Entity& entity, const EntityState& state);

    // Trait API
    void registerTrait (unsigned int trait, TraitFactory* factory);
    AbstractTrait* getTrait (unsigned int entity, unsigned int trait);
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
