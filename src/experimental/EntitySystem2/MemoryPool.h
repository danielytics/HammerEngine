#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

//class MemoryPool
//{
//public:
//    virtual ~MemoryPool () {}
//    virtual void* request () = 0;
//    virtual void release (void*) = 0;
//};

#include "DebugTools.h"
#include "TemplateTools.h"
template <int Size> struct CalculateObjectSize
{
    // Calculate object size by making sure its size is a multiple of 16 bytes
    enum { ObjectSize = (Size & 0xf) // Is Size already correct?
                        ? /* No, pad with extra bytes   */ (((Size / 16) + 1 /* add another 16 bytes */) * 16)
                        : /* Yes, return Size unchanged */ Size};
};

template <int MaxBlockSize, int ObjectSize> struct CalculateBlockSize
{
    // We want to preallocate about MaxBlockSize KB worth of objects.
    enum { NumObjects = static_if<ObjectSize <= (MaxBlockSize / 2), // if
                            value_type<MaxBlockSize / ObjectSize>,   // then
                            compile_error(true, Memory_pool_objects_must_not_be_larger_than_half_of_MaxBlockSize) // else, ERROR: Memory pool does not support objects larger than 1KB
                        >::Type::Value};
};

namespace MemoryFeatures
{
    template <int Size=2048> struct DynamicPool
    {
        enum { BlockSize = Size }; // Size of block, in KB
    };
    typedef DynamicPool<> DefaultDynamicPoolFeatures;

    template <int Objects=128> struct StaticPool
    {
        enum { BlockSize = Objects }; // Size of blocks, in objects
    };
    typedef StaticPool<> DefaultStaticPoolFeatures;
}

template <template <class, class, int> class PoolType, class Feature, class Object> struct CreateMemoryPool
{
    typedef PoolType<Feature, Object, Feature::BlockSize> Type;
};

#endif // MEMORYPOOL_H
