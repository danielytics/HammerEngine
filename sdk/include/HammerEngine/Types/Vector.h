#ifndef HAMMER_ENGINE_VECTOR__H_
#define HAMMER_ENGINE_VECTOR__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/GenericVector.h>

class Vector : public GenericVector<Vector, 3>
{
private:
    static const unsigned int X = 0;
    static const unsigned int Y = 1;
    static const unsigned int Z = 2;
public:
    Packed& x () {
        return get(X);
    }

    Packed& y () {
        return get(Y);
    }
    Packed& z () {
        return get(Z);
    }

    Packed length () const
    {

    }

    Vector normalized () const
    {

    }

    Packed dotProduct () const
    {

    }

};

#endif // HAMMER_ENGINE_VECTOR__H_
