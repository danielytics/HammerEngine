#ifndef HAMMER_ENGINE_TRAITBUILDER__H_
#define HAMMER_ENGINE_TRAITBUILDER__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "EntitySystem.h"
#include "Trait.h"
#include "AlignedMemoryPool.h"
#include "DebugTools.h"

#include <tbb/concurrent_unordered_map.h>
#include <vector>
#include <algorithm>


class TraitFactory
{
public:
    virtual ~TraitFactory() {}

    virtual AbstractTrait::Type create (unsigned int) = 0;
    virtual void destroy (unsigned int) = 0;
    virtual AbstractTrait::Type lookup (unsigned int)=0;
    virtual void getEntities (std::vector<unsigned int>&)=0;
};

template <class Feature, class T> class TraitFactoryWrapper : public TraitFactory
{
private:
    typedef Trait<T> TraitType;
    typename CreateMemoryPool<AlignedMemoryPool, Feature, TraitType>::Type pool;

    typedef typename tbb::concurrent_unordered_map<unsigned int, TraitType*>::iterator IterType;
    tbb::concurrent_unordered_map<unsigned int, TraitType*> entityMap;
    std::vector<unsigned int> listOfEntities;

public:
    TraitFactoryWrapper () {}
    virtual ~TraitFactoryWrapper () {}

    /**
      * Create a new trait object and return an AbstractTrat type.
      *
      * WARNING: Not thread safe!
      */
    AbstractTrait::Type create (unsigned int entity)
    {
        IterType iter = entityMap.find(entity);
        if (iter == entityMap.end())
        {
            TraitType* trait = pool.request(); // This call is NOT thread safe!
            assert_not_null(trait);
            entityMap[entity] = trait;
            listOfEntities.push_back(entity); // This call is NOT thread safe!
            return AbstractTrait::from_ptr(trait);
        }
        return AbstractTrait::from_ptr((*iter).second);
    }

    /**
      * Destroy a trait object.
      *
      * WARNING: Not thread safe!
      */
    void destroy (unsigned int entity)
    {
        IterType iter = entityMap.find(entity);
        if (iter != entityMap.end())
        {
            TraitType* t = deref_iter(iter, entityMap).second;
            assert_not_null(t);

            // Next line is NOT thread safe!
            std::vector<unsigned int>::iterator it = std::find(listOfEntities.begin(), listOfEntities.end(), entity);
            if (it != listOfEntities.end())
            {
                *it = listOfEntities.back(); // This call is NOT thread safe!
                listOfEntities.pop_back(); // This call is NOT thread safe!
            }
            entityMap.unsafe_erase(iter); // This call is NOT thread safe!
            pool.release(t); // This call is NOT thread safe!

        }
    }

    /**
      * Lookup a trait by entity id and return its AbstractTrait type.
      *
      * Thread safe.
      */
    AbstractTrait::Type lookup (unsigned int entity)
    {
        IterType iter = entityMap.find(entity);
        if (iter != entityMap.end())
        {
            return AbstractTrait::from_ptr(deref_iter(iter, entityMap).second);
        }
        return AbstractTrait::from_ptr<T>(0);
    }

    /**
      * Get a vector of entity ids for all entities which contain traits in this factory.
      *
      * Thread safe.
      */
    void getEntities (std::vector<unsigned int>& entities)
    {
        entities = listOfEntities;
//        IterType iter = entityMap.begin();
//        while (iter != entityMap.end())
//        {
//            entities.push_back(deref_iter(iter, entityMap).first);
//            ++iter;
//        }
    }
};

class TraitBuilder
{
private:
    EntitySystem* entitySystem;
public:
    TraitBuilder (EntitySystem* ngin) : entitySystem(ngin) {assert_not_null(entitySystem);}
    ~TraitBuilder () {}

    template <class Features, class T>
    void registerTrait ()
    {
        entitySystem->registerTrait(Trait<T>::id(), new TraitFactoryWrapper<Features, T>());
    }
};

#endif // HAMMER_ENGINE_TRAITBUILDER__H_
