#ifndef HAMMER_ENGINE_GENERICVECTOR__H_
#define HAMMER_ENGINE_GENERICVECTOR__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/Packed.h>

#define GV_FOREACH(op)  T temp;\
                        for (unsigned int index = 0; index < N; ++index) {\
                            temp.vectors[index] = op(vectors[index], other.vectors[index]);\
                        } return temp

/**
  * GenericVector<T, N>
  *
  * Generic vector of N packed floats, to implement T.
  *
  */
template <class T, unsigned int N> class GenericVector
{
private:
    Packed vectors[N];

protected:
    T& get (const unsigned int index) const
    {
        return vectors[index]        ;
    }

public:
    GenericVector () {}
    virtual ~GenericVector () {}

    inline T operator+ (const T& other) const
    {
        GV_FOREACH(Packed::add);
    }

    inline T operator- (const T& other) const
    {
        GV_FOREACH(Packed::sub);
    }

    inline T operator* (const T& other) const
    {
        GV_FOREACH(Packed::mul);
    }

    static const unsigned int stream_size = N;
};

#undef GV_FOREACH

#endif // HAMMER_ENGINE_GENERIC_VECTOR__H_
