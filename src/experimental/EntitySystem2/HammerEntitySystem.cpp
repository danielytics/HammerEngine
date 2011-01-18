
#include <iostream>

#include "HammerEntitySystem.h"
#include "TraitBuilder.h"
#include "Entity.h"
#include "BehaviorFunctor.h"

#include "DebugTools.h"

#include <iostream>

//#include "MemoryPool.h"

//class CacheAlignedChunkedMemoryPool : public MemoryPool
//{
//private:
//    const unsigned int elementSize;
//    const unsigned int elementsPerBlock;
//    const unsigned int blockSize;

//    struct Block
//    {
//        Block* next;
//        char* elements;
//        // Memory for elements is placed after the struct...
//    };

//    Block* blockList;
//    Block* lastBlock;
//    char* freeList;

//    void initBlock (Block* block)
//    {
//        block->next = 0;
//        block->elements = reinterpret_cast<char*>(block) + sizeof(Block);

//        // Get the first element in the block
//        char* ptr = deref(block)->elements;

//        // Set the last link to point to null
//        *reinterpret_cast<char**>(ptr + blockSize  - elementSize) = 0;

//        // For a block to be inited, freeList must be empty, so set the new block as the freeList
//        freeList = ptr;

//        // Set every other link to point to the next element in the chain
//        for (unsigned int i = elementsPerBlock - 1; i; --i)
//        {
//            char* next = ptr + elementSize;
//            *deref(reinterpret_cast<char**>(ptr)) = next;
//            ptr = next;
//        }
//    }

//    void allocateBlock ()
//    {
//        lastBlock->next = reinterpret_cast<Block*>(new char[blockSize + sizeof(Block)]);
//        lastBlock = lastBlock->next;
//        initBlock(lastBlock);
//    }

//public:
//    CacheAlignedChunkedMemoryPool (unsigned int es, unsigned int bs)
//        : elementSize(es)
//        , elementsPerBlock(bs)
//        , blockSize(es * bs)
//    {
//        lastBlock = reinterpret_cast<Block*>(new char[blockSize + sizeof(Block)]);
//        blockList = lastBlock;
//        initBlock(lastBlock);
//    }
//    virtual ~CacheAlignedChunkedMemoryPool ()
//    {
//        while (blockList != 0)
//        {
//            lastBlock = blockList->next;
//            delete [] reinterpret_cast<char*>(blockList);
//            blockList = lastBlock;
//        }
//    }

//    void* request ()
//    {
//        if (freeList == 0)
//        {
//            allocateBlock();
//        }
//        void* buffer = reinterpret_cast<void*>(freeList);
//        freeList = *deref(reinterpret_cast<char**>(freeList));
//        return buffer;
//    }

//    void release (void* addr)
//    {
//        if (addr < freeList || freeList == 0)
//        {
//            *deref(reinterpret_cast<char**>(addr)) = freeList;
//            freeList = reinterpret_cast<char*>(addr);
//        } else
//        {
//            char* current = freeList;
//            char* next = *deref(reinterpret_cast<char**>(freeList));
//            while (next != 0)
//            {
//                if (addr < next) break;
//                current = next;
//                next = *deref(reinterpret_cast<char**>(next + elementSize));
//            }

//            *reinterpret_cast<char**>(current) = reinterpret_cast<char*>(addr);
//            *reinterpret_cast<char**>(addr) = next;
//        }
//    }
//};


HammerEntitySystem::HammerEntitySystem () :
        next_id(0)
{
    invalidEntity = new Entity(*this, (unsigned int)-1);
}

HammerEntitySystem::~HammerEntitySystem ()
{
    for (std::vector<Entity*>::iterator iter = entityList.begin(); iter != entityList.end(); ++iter)
    {
        delete *iter;
    }
    // TODO: delete traits
}

// Entity API
Entity& HammerEntitySystem::createEntity ()
{
    Entity* entity = new Entity(*this, entityList.size()); // TODO: Memory pool
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
