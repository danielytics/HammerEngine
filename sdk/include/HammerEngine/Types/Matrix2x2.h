#ifndef HAMMER_ENGINE_MATRIX2X2__H_
#define HAMMER_ENGINE_MATRIX2X2__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/GenericVector.h>

/*

| a b |
| c d |

*/

class Line : public GenericVector<Line, 4>
{
private:
    static const unsigned int TOP_LEFT     = 0;
    static const unsigned int TOP_RIGHT    = 1;
    static const unsigned int BOTTOM_LEFT  = 2;
    static const unsigned int BOTTOM_RIGHT = 3;

public:
    Color () : GenericVector() {}
    virtual ~Color () {}

    Packed& tl () {
        return get(TOP_LEFT);
    }

    Packed& tr () {
        return get(TOP_RIGHT);
    }

    Packed& bl () {
        return get(BOTTOM_LEFT);
    }

    Packed& br () {
        return get(BOTTOM_RIGHT);
    }

    // Packed length () const;
    // Vector midpoint () const;
};


#endif // HAMMER_ENGINE_MATRIX2X2__H_
