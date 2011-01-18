#ifndef HAMMER_ENGINE_LINE__H_
#define HAMMER_ENGINE_LINE__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/GenericVector.h>

class Line : public GenericVector<Line, 6>
{
private:
    static const unsigned int X1 = 0;
    static const unsigned int Y1 = 1;
    static const unsigned int Z1 = 2;
    static const unsigned int X2 = 3;
    static const unsigned int Y2 = 4;
    static const unsigned int Z2 = 5;

public:
    Color () : GenericVector() {}
    virtual ~Color () {}

    Packed& x1 () {
        return get(X1);
    }

    Packed& y1 () {
        return get(Y1);
    }

    Packed& x2 () {
        return get(X2);
    }

    Packed& y2 () {
        return get(Y2);
    }

    // Packed length () const;
    // Vector midpoint () const;
};

#endif // HAMMER_ENGINE_LINE__H_
