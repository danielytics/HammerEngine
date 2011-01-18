#ifndef ALIGNEDMEMORYPOOL_H
#define ALIGNEDMEMORYPOOL_H

#include "DebugTools.h"
#include "MemoryPool.h"
#include "BlockMemoryPoolImpl.h"

#include <typeinfo>

template <class Feature, class Object, int PoolSize> class AlignedMemoryPool : invalid_template(Feature, Attempted_to_instantiate_AlignedMemoryPool_with_unsupported_feature)
{
    // AlignedMemoryPool with invalid Features, if a template evaluates to this, a compile error is produced
};

/**
  * Static AlignedMemoryPool
  * A memory pool whose objects are aligned to a 16-byte boundary, which is a static size.
  * Throws an exception if an object is requested when all objects in the pool are used.
  */
template <class Object, int PoolSize> class AlignedMemoryPool<MemoryFeatures::StaticPool<PoolSize>, Object, PoolSize>
{
private:
    enum {ObjectSize = CalculateObjectSize<sizeof(Object)>::ObjectSize}; // Calculate the 16-byte aligned object size

    union BlockObject {
        char buffer[ObjectSize]; // Make sure union size is 16-byte aligned
        BlockObject* nextUnused; // Maintain links to unused objects
    };
    BlockObject objects[PoolSize]; // Static array of objects
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
    AlignedMemoryPool ()
    {
        // Point freeList at the first object
        freeList = BlockMemoryPoolImplementation::initBlock<BlockObject, PoolSize>(objects);
    }

    ~AlignedMemoryPool ()
    {

    }

    template <class Ctor> Object* request (Ctor& ctor)
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            // TODO: Do we want an eviction policy??
            std::ostringstream sstr;
            sstr << "Static AlignedMemoryPool is out of objects of type " << typeid(Object).name();
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
  * Dynamic AlignedMemoryPool
  * A memory pool whose objects are aligned to a 16-byte boundary, which dynamically grows to fit requested objects.
  */
template <class Object, int PoolSize> class AlignedMemoryPool<MemoryFeatures::DynamicPool<PoolSize>, Object, PoolSize>
{
private:
    enum {ObjectSize = CalculateObjectSize<sizeof(Object)>::ObjectSize,       // Calculate the 16-byte aligned object size
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
    Block staticBlock;
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
    AlignedMemoryPool ()
        : root(&staticBlock) // First block is statically allocated
        , freeList(BlockMemoryPoolImplementation::initBlock<BlockObject, BlockSize>(staticBlock.objects))
    {
        staticBlock.next = 0;
    }

    ~AlignedMemoryPool ()
    {
        Block* next = root;
        Block* temp;
        while (next)
        {
            temp = next;
            next = next->next;
            if (temp != &staticBlock) delete temp;
        }
    }

    template <class Ctor> inline Object* request (Ctor& ctor)
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            Block* block = new Block;
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

#endif // ALIGNEDMEMORYPOOL_H
