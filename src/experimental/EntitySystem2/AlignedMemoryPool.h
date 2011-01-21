#ifndef ALIGNEDMEMORYPOOL_H
#define ALIGNEDMEMORYPOOL_H

#include "DebugTools.h"
#include "MemoryPool.h"
#include "BlockMemoryPoolImpl.h"

#include <typeinfo>
#include <sstream>
#include <xmmintrin.h> // needed for _mm_malloc

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
    AlignedMemoryPool ()
        : objects(reinterpret_cast<BlockObject*>(_mm_malloc(sizeof(BlockObject) * PoolSize, 16))) // Allocate static memory aligned to hold any BlockObject // TODO: make sure this is 16-byte aligned
    {
        // Point freeList at the first object
        freeList = BlockMemoryPoolImplementation::initBlock<BlockObject, PoolSize>(*deref(objects));
        assert_align(objects, 16);
    }

    ~AlignedMemoryPool ()
    {
        delete [] objects;
    }

    template <class Ctor> Object* request (Ctor& ctor)
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            std::ostringstream sstr;
            sstr << "Static AlignedMemoryPool is out of objects of type " << typeid(Object).name();
            throw std::runtime_error(sstr.str());
        }
        Object* obj = BlockMemoryPoolImplementation::getUnusedObject<BlockObject, Object, Ctor>(freeList, ctor);
        assert_align(obj, 16);
        return obj;
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
    struct Block
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
    AlignedMemoryPool ()
        : root(reinterpret_cast<Block*>(_mm_malloc(sizeof(Block), 16))) // First block is allocated at construction, 'new char[x]' is guaranteed to be properly aligned for any obejct equal to or less than x
        , freeList(BlockMemoryPoolImplementation::initBlock<BlockObject, BlockSize>(root->objects))
    {
        root->next = 0;
        assert_align(root->objects, 16);
    }

    ~AlignedMemoryPool ()
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

    template <class Ctor> inline Object* request (Ctor& ctor)
    {
        if (!freeList)
        {
            // There are no more free objects in the pool, allocate more.
            Block* block = reinterpret_cast<Block*>(_mm_malloc(sizeof(Block), 16)); // 'new char[x]' is guaranteed to be properly aligned for any obejct equal to or less than x
            assert_align(block->objects, 16);
            block->next = root;
            root = block;
            freeList = BlockMemoryPoolImplementation::initBlock<BlockObject, BlockSize>(block->objects);
        }
        Object* obj = BlockMemoryPoolImplementation::getUnusedObject<BlockObject, Object, Ctor>(freeList, ctor);
        assert_align(obj, 16);
        return obj;
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
