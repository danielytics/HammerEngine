#ifndef HAMMER_ENGINE_COLOR__H_
#define HAMMER_ENGINE_COLOR__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/GenericVector.h>

class Color : public GenericVector<Color, 3>
{
private:
    static const unsigned int R = 0;
    static const unsigned int G = 1;
    static const unsigned int B = 2;

public:
    Color () : GenericVector() {}
    virtual ~Color () {}

    Packed& r () {
        return get(R);
    }

    Packed& g () {
        return get(G);
    }
    Packed& b () {
        return get(B);
    }

    // Clamp each component to the [0,1] range.
    void clamp ()
    {
        Packed& red   = get(R);
        Packed& green = get(G);
        Packed& blue  = get(B);

        Packed zero(0.0f, 0.0f, 0.0f, 0.0f);
        Packed ones(1.0f, 1.0f, 1.0f, 1.0f);

        red = Packed::max(zeros, Packed::min(red, ones));
        green = Packed::max(zeros, Packed::min(green, ones));
        blue = Packed::max(zeros, Packed::min(blue, ones));
    }
};

#endif // HAMMER_ENGINE_COLOR__H_
