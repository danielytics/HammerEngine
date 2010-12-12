#ifndef POOLED_H
#define POOLED_H

#include <memory>

enum PoolFlags
{
    /*
     * Dummy enums
     * Always 0, so thatt hey do not affect the flags, used when an absense of an effect is desired.
     */

    // Allocated objects do not need to be 16-byte aligned
    UNALIGNED               = 0x00,

    // If BLOCK_ALLOC is selected, this flag specifies that the default number of objects are allocated per block
    DEFAULT_BLOCK_SIZE      = 0x00,

    /*
     * Flag enums
     * Set specific memory pool behaviour.
     */

    // Allocated objects should be 16-byte aligned
    ALIGNED                 = 0x01, // 0001

    // When the pool needs more memory, allocate it in blocks of multiple objects
    BLOCK_ALLOC             = 0x02, // 0010

    // Allocate the pools memory using a (multicore) scalable allocator
    SCALABLE                = 0x04, // 0100

    // If BLOCK_SIZE is selected, this flag specifies that a custom number of objects are allocated per block and the size is packed into the top 8 bits of the flags
    NON_DEFAULT_BLOCK_SIZE  = 0x08, // 1000

};

#define PACK_POOL_BLOCK_SIZE(size)      ((0xff & (size)) << 24)
#define UNPACK_POOL_BLOCK_SIZE(flags)   (((flags) >> 24) & 0xff)
#define BLOCK_SIZE(size)                (NON_DEFAULT_BLOCK_SIZE | PACK_POOL_BLOCK_SIZE((size)))

template <class T> class Pooled
{
private:

public:
    virtual ~Pooled ()
    {

    }

    void* operator new (size_t size);
    void operator delete (void *p);
};

#define POOLED_OBJECT                                           \
    public:                                                     \
        void* operator new (size_t size);                       \
        void operator delete (void *p);                         \
    private:                                                    \
        static MemoryPool objectMemoryPool;

#define INIT_POOLED_OBJECT(cls, flags)                          \
        MemoryPool cls::objectMemoryPool(sizeof(cls), (flags)); \
        void* cls::operator new (size_t size) {                 \
            void* ptr = objectMemoryPool.request();             \
            if (ptr == 0) throw std::bad_alloc();               \
            return ptr;                                         \
        }                                                       \
        void cls::operator delete (void* p) {                   \
            objectMemoryPool.release(p);                        \
        }

#define INIT_POOLED_OBJECT_DEFAULT(cls) INIT_POOLED_OBJECT(cls, UNALIGNED | BLOCK_ALLOC | DEFAULT_BLOCK_SIZE)



/*
Example:

class Foo
{
    POOLED_OBJECT
public:
    int bar;
public:
    Foo () {}
    virtual ~Foo () {}

    int baz () {
        return bar;
    }
};

// Objects are 16-bytes aligned, allocated using a scalable malloc in blocks of 32
INIT_POOLED_OBJECT(Foo, ALIGNED | BLOCK_ALLOC | BLOCK_SIZE(32) | SCALABLE);

...

Foo* f = new Foo;
delete f;

*/

#endif // POOLED_H
