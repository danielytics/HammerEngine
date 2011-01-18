#ifndef HAMMER_ENGINE_TRAITBUILDER__H_
#define HAMMER_ENGINE_TRAITBUILDER__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <map>
#include <vector>

#include "EntitySystem.h"
#include "Trait.h"
#include "AlignedMemoryPool.h"
#include "DebugTools.h"

#include <unordered_map>

class TraitFactory
{
public:
    virtual ~TraitFactory() {}

    virtual AbstractTrait* create (unsigned int) = 0;
    virtual void destroy (unsigned int) = 0;
    virtual AbstractTrait* lookup (unsigned int)=0;
    virtual void getEntities (std::vector<unsigned int>&)=0;
};

template <class Feature, class T> class TraitFactoryWrapper : public TraitFactory
{
private:
    typedef Trait<T> TraitType;
    typename CreateMemoryPool<AlignedMemoryPool, Feature, TraitType>::Type pool;

    typedef typename std::unordered_map<unsigned int, TraitType*>::iterator IterType;
    std::unordered_map<unsigned int, TraitType*> entityMap;

public:
    TraitFactoryWrapper () {}
    virtual ~TraitFactoryWrapper () {}

    AbstractTrait* create (unsigned int entity)
    {
        IterType iter = entityMap.find(entity);
        if (iter == entityMap.end())
        {
            TraitType* trait = pool.request();
            entityMap[entity] = trait;
            return trait;
        }
        return (*iter).second;
    }

    void destroy (unsigned int entity)
    {
        IterType iter = entityMap.find(entity);
        if (iter != entityMap.end())
        {
            TraitType* t = deref_iter(iter, entityMap).second;
            entityMap.erase(iter);
            pool.release(t);

        }
    }

    AbstractTrait* lookup (unsigned int entity)
    {
        IterType iter = entityMap.find(entity);
        if (iter != entityMap.end())
        {
            return deref_iter(iter, entityMap).second;
        }
        return 0;
    }

    void getEntities (std::vector<unsigned int>& entities)
    {
        IterType iter = entityMap.begin();
        while (iter != entityMap.end())
        {
            entities.push_back(deref_iter(iter, entityMap).first);
            ++iter;
        }
    }
};

class TraitBuilder
{
private:
    EntitySystem* entitySystem;
public:
    TraitBuilder (EntitySystem* ngin) : entitySystem(ngin) {}
    ~TraitBuilder () {}

    template <class Features, class T>
    void registerTrait ()
    {
        entitySystem->registerTrait(Trait<T>::id(), new TraitFactoryWrapper<Features, T>());
    }
};

#endif // HAMMER_ENGINE_TRAITBUILDER__H_
