#ifndef UNALIGNEDMEMORYPOOL_H
#define UNALIGNEDMEMORYPOOL_H

#include "DebugTools.h"
#include "MemoryPool.h"
#include "BlockMemoryPoolImpl.h"

#include <typeinfo>
#include <sstream>

template <class Feature, class Object, int PoolSize> class UnalignedMemoryPool : invalid_template(Feature, Attempted_to_instantiate_UnalignedMemoryPool_with_unsupported_feature)
{
    // UnalignedMemoryPool with invalid Features, if a template evaluates to this, a compile error is produced
};

/**
  * Static UnalignedMemoryPool
  * A memory pool whose objects are not aligned to a 16-byte boundary (but guaranteed to be aligned correctly for the object it pools), which is a static size.
  * Throws an exception if an object is requested when all objects in the pool are used.
  */
template <class Object, int PoolSize> class UnalignedMemoryPool<MemoryFeatures::StaticPool<PoolSize>, Object, PoolSize>
{
private:
    enum {ObjectSize = sizeof(Object)}; // Object size does not need to be adjusted as the pool is unaligned

    union BlockObject {
        char buffer[ObjectSize]; // Make sure union size is 16-byte aligned
        BlockObject* nextUnused; // Maintain links to unused objects
    };
    BlockObject* objects[PoolSize]; // Static array of objects
    BlockObject* freeList;

    struct StandardCtor
    {
        inline Object* construct (char* buffer)
        {
            return new (buffer) Object();
        }
    };
    StandardCtor standardCtor;

public:
    UnalignedMemoryPool ()
        : objects(new char[sizeof(BlockObject) * PoolSize]) // 'new char[x]' is guaranteed to be properly aligned for any obejct equal to or less than x
    {
        // Point freeList at the first object
        freeList = BlockMemoryPoolImplementation::initBlock<BlockObject, PoolSize>(*deref(objects));
    }

    ~UnalignedMemoryPool ()
    {
        delete [] objects;
    }

    template <class Ctor> Object* request (Ctor& ctor)
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            // TODO: Do we want an eviction policy??
            std::ostringstream sstr;
            sstr << "Static UnalignedMemoryPool is out of objects of type " << typeid(Object).name();
            throw std::runtime_error(sstr.str());
        }
        return BlockMemoryPoolImplementation::getUnusedObject<BlockObject, Object, Ctor>(freeList, ctor);
    }

    Object* request ()
    {
        return request<StandardCtor>(standardCtor);
    }

    void release (Object* pointer)
    {
        BlockMemoryPoolImplementation::setObjectUnused<BlockObject, Object>(freeList, pointer);
    }
};

/**
  * Dynamic UnalignedMemoryPool
  * A memory pool whose objects are not aligned to any specific byte boundary, which dynamically grows to fit requested objects.
  */
template <class Object, int PoolSize> class UnalignedMemoryPool<MemoryFeatures::DynamicPool<PoolSize>, Object, PoolSize>
{
private:
    enum {ObjectSize = sizeof(Object),                                        // Object size does not need to be adjusted as the pool is unaligned
          BlockSize  = CalculateBlockSize<PoolSize, ObjectSize>::NumObjects}; // Calculate a reaosnable number of objects per block based on object size

    union BlockObject {
        char buffer[ObjectSize]; // Make sure union size is 16-byte aligned
        BlockObject* nextUnused; // Maintain links to unused objects
    };
    struct Block // TODO: make sure Block is aligned (add attributes to align static block and use aligned malloc to allocate new blocks)
    {
        BlockObject objects[BlockSize];
        Block* next;
    };
    Block* root;
    BlockObject* freeList;

    struct StandardCtor
    {
        inline Object* construct (char* buffer)
        {
            return new (buffer) Object();
        }
    };
    StandardCtor standardCtor;

public:
    UnalignedMemoryPool ()
        : root(reinterpret_cast<Block*>(new char[sizeof(Block)])) // First block is statically allocated, 'new char[x]' is guaranteed to be properly aligned for any obejct equal to or less than x
        , freeList(BlockMemoryPoolImplementation::initBlock<BlockObject, BlockSize>(root->objects))
    {
        root->next = 0;
    }

    ~UnalignedMemoryPool ()
    {
        Block* next = root;
        Block* temp;
        while (next)
        {
            temp = next;
            next = next->next;
            delete [] reinterpret_cast<char*>(temp);
        }
    }

    template <class Ctor> Object* request (Ctor& ctor)
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            Block* block = reinterpret_cast<Block*>(new char[sizeof(Block)]); // 'new char[x]' is guaranteed to be properly aligned for any obejct equal to or less than x
            block->next = root;
            root = block;
            freeList = BlockMemoryPoolImplementation::initBlock<BlockObject, BlockSize>(block->objects);
        }
        return BlockMemoryPoolImplementation::getUnusedObject<BlockObject, Object, Ctor>(freeList, ctor);
    }

    Object* request ()
    {
        return request<StandardCtor>(standardCtor);
    }

    void release (Object* pointer)
    {
        BlockMemoryPoolImplementation::setObjectUnused<BlockObject, Object>(freeList, pointer);
    }
};

#endif // UNALIGNEDMEMORYPOOL_H
