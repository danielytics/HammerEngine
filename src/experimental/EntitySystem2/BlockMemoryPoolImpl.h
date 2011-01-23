#ifndef BLOCKMEMORYPOOLIMPL_H
#define BLOCKMEMORYPOOLIMPL_H

#include "Null.h"

namespace BlockMemoryPoolImplementation
{
    template <class T, int NumObjects> inline T* initBlock (T objects[NumObjects])
    {
        assert_not_null(objects);
        // Initialize the pool for use
        const unsigned int maxIndex = NumObjects - 1;
        objects[maxIndex].nextUnused = nullptr;
        for (unsigned int index = 0; index < maxIndex; ++index)
        {
            assert(index < NumObjects);
            objects[index].nextUnused = &objects[index + 1];
        }
        return objects;
    }

    template <class T, class Object, class Ctor> inline Object* getUnusedObject (T*& freeList, Ctor& ctor)
    {
        T* object = freeList;
        assert_not_null(object);
        freeList = object->nextUnused;
        return ctor.construct(object->buffer);
    }

    template <class T, class Object> inline void setObjectUnused (T*& freeList, Object* pointer)
    {
        assert_not_null(pointer);
        pointer->~Object();
        T* object = reinterpret_cast<T*>(pointer);
        object->nextUnused = freeList;
        freeList = object;
    }
};

#endif // BLOCKMEMORYPOOLIMPL_H
