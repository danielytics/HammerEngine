#ifndef HAMMER_ENGINE_TRAIT__H_
#define HAMMER_ENGINE_TRAIT__H_

#include <typeinfo>
#include "SimdMacros.h"

struct AbstractTrait
{
    typedef unsigned int Type;
    template <class T> static inline T* to_ptr (Type trait)
    {
        return reinterpret_cast<T*>(trait);
    }
    template <class T> static inline Type from_ptr (T* ptr)
    {
        return reinterpret_cast<Type>(ptr);
    }
};

template <class T> class Trait
{
public:
    Trait () : data() {}
    Trait (T& d) : data(&d) {}
    ~Trait () {}

    typedef T trait_type;
    ALIGNED( T data);

    static inline unsigned int id ()
    {
        static const unsigned int idnum = (unsigned int)(typeid(T).name()); // TODO: Fix This!
        return idnum;
    }
};

#endif // HAMMER_ENGINE_TRAIT__H_
