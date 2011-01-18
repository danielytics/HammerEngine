#ifndef STATICMEMORYPOOL_H
#define STATICMEMORYPOOL_H

#include "DebugTools.h"
#include "MemoryPool.h"

#include <stdexcept>

template <class Feature, class Object, int PoolSize> class AlignedMemoryPool : invalid_template(Feature, Attempted_to_instantiate_AlignedMemoryPool_with_unsupported_feature)
{
    // AlignedMemoryPool with invalid Features, if a template evaluates to this, a compile error is produced
};

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

public:
    AlignedMemoryPool ()
    {
        // Initialize the pool for use
        const unsigned int maxIndex = PoolSize - 1;
        objects[maxIndex].nextUnused = 0;
        for (unsigned int index = 0; index < maxIndex; ++index)
        {
            assert(index < PoolSize);
            objects[index].nextUnused = &objects[index + 1];
        }
        // Point freeList at the first object
        freeList = objects;
    }

    ~AlignedMemoryPool ()
    {

    }

    Object* request ()
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            // TODO: Do we want an eviction policy??
            std::ostringstream sstr;
            sstr << "Static AlignedMemoryPool is out of objects of type " << typeid(Object).name();
            throw std::runtime_error(sstr.str());
        }
        BlockObject* object = freeList;
        assert(object != 0);
        freeList = object->nextUnused;
        return new (object->buffer) Object();
    }

    void release (Object* pointer)
    {
        assert(pointer != 0);
        pointer->~Object();
        BlockObject* object = reinterpret_cast<BlockObject*>(pointer);
        object->nextUnused = freeList;
        freeList = object;
    }
};

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

    Block* initBlock (Block* block)
    {
        assert(block != 0);
        const unsigned int maxIndex = BlockSize - 1;
        block->objects[maxIndex].nextUnused = 0;
        for (unsigned int index = 0; index < maxIndex; ++index)
        {
            assert(index < BlockSize);
            block->objects[index].nextUnused = &block->objects[index + 1];
        }
        return block;
    }


public:
    AlignedMemoryPool ()
        : root(initBlock(&staticBlock)) // First block is statically allocated
        , freeList(staticBlock.objects)
    {

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

    Object* request ()
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            Block* block = initBlock(new Block);
            block->next = root;
            freeList = block->objects;
        }
        BlockObject* object = freeList;
        assert(object != 0);
        freeList = object->nextUnused;
        return new (object->buffer) Object();
    }

    void release (Object* pointer)
    {
        assert(pointer != 0);
        pointer->~Object();
        BlockObject* object = reinterpret_cast<BlockObject*>(pointer);
        object->nextUnused = freeList;
        freeList = object;
    }
};

#endif // STATICMEMORYPOOL_H
