#ifndef HAMMER_ENGINE_COLOR4__H_
#define HAMMER_ENGINE_COLOR4__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/GenericVector.h>

class Color4 : public GenericVector<Color4, 4>
{
private:
    static const unsigned int R = 0;
    static const unsigned int G = 1;
    static const unsigned int B = 2;
    static const unsigned int A = 3;

public:
    Color4 () : GenericVector() {}
    virtual ~Color4 () {}

    Packed& r () {
        return get(R);
    }

    Packed& g () {
        return get(G);
    }

    Packed& b () {
        return get(B);
    }

    Packed& a () {
        return get(A);
    }
};

#endif // HAMMER_ENGINE_COLOR4__H_
