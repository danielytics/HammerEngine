#ifndef HAMMER_ENGINE_STREAMPOOL__H_
#define HAMMER_ENGINE_STREAMPOOL__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/Packed.h>

class StreamPool;

class Stream
{
private:
    const StreamPool* pool;
    const unsigned int stride;

    unsigned int length;
    const float* stream;
    float* writeptr;

    inline void write (const Packed& packed)
    {
        packed.store(write);
        writeptr += 4;
    }

public:
    Stream (const StreamPool* p, const unsigned int streamStride) :
            pool(p),
            stride(streamStride),
            index(0),
            component(0)
    {
    }
    ~Stream ()
    {
        pool->release(stream);
    }

    /**
      * Unpack a packed float into a 16-byte aligned float array.
      * [x1,x2,x3,x4] => {x1,x2,x3,x4}
      */
    void unpack (const Packed& RESTRICTED_PTR packed)
    {
        write(packed);
        length += 4;
    }

    /**
      * Unpack and interleave two packed floats into a 16-byte aligned float array.
      * [x1,x2,x3,x4], [y1, y2, y3, y4] => {x1,y1,x2,y2,x3,y3,x4,y4}
      */
    void unpack (const Packed& RESTRICTED_PTR x, const Packed& RESTRICTED_PTR y)
    {
        // X = [x1, x2, x3, x4], Y = [y1, y2, y3, y4]
        // output = [x1, y1, x2, y2, x3, y3, x4, y4]
        pack(y.interleave_hi(x)); // [x1, y1, x2, y2]
        pack(y.interleave_lo(x)); // [x3, y3, x4, y4]
        length += 8;
    }

    /**
      * Unpack and interleave three packed floats into a 16-byte aligned float array.
      * [x1,x2,x3,x4], [y1, y2, y3, y4], [z1,z2,z3,z4] => {x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4}
      */
    void unpack (const Packed& RESTRICTED_PTR x, const Packed& RESTRICTED_PTR y, const Packed& RESTRICTED_PTR z)
    {
        // X = [x1, x2, x3, x4], Y = [y1, y2, y3, y4], Z = [z1, z2, z3, z4]
        // output = [x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4]

        /* Desired output: [x1, y1, z1, x2]
         * A: interleave_hi(Y, X)       => [x1, y1, x2, y2]
         * B: interleave_hi(Z, X)       => [x1, z1, x2, z2]
         * C: shuffle<2, 1, 1, 0>(B, A) => [x1, y1, z1, x2]
         */
        write(/* B */z.interleave_hi(x)
              /* C */.shuffle<2, 1, 1, 0>(
              /* A */y.interleave_hi(x)));

        /* Desired output: [y2, z2, x3, y3]
         * A: interleave_hi(Y, Z)       => [z1, y1, z2, y2]
         * B: interleave_lo(Y, X)       => [x3, y3, x4, y4]
         * C: shuffle<1, 0, 2, 3>(B, A) => [y2, z2, x3, y3]
         */
        write(/* B */y.interleave_lo(x)
              /* C */.shuffle<1, 0, 2, 3>(
              /* A */y.interleave_hi(z)));

        /* Desired output: [z3, x4, y4, z4]
         * A: interleave_lo(Z, Y)       => [y3, z3, y4, z4]
         * B: interleave_lo(X, Z)       => [z3, x3, z4, x4]
         * C: shuffle<3, 2, 3, 0>(A, B) => [z3, x4, y4, z4]
         */
        write(/* A */z.interleave_lo(y)
              /* C */.shuffle<3, 2, 3, 0>(
              /* B */x.interleave_lo(z)));

        length += 12;

    }

    /**
      * Unpack and interleave four packed floats into a 16-byte aligned float array.
      * [x1,x2,x3,x4], [y1, y2, y3, y4], [z1,z2,z3,z4], [w1, w2, w3, w4] => {x1,y1,z1,w1,x2,y2,z2,w2,x3,y3,z3,w3,x4,y4,z4,w4}
      */
    void unpack (const Packed& RESTRICTED_PTR x, const Packed& RESTRICTED_PTR y, const Packed& RESTRICTED_PTR z, const Packed& RESTRICTED_PTR w)
    {
        // X = [x1, x2, x3, x4], Y = [y1, y2, y3, y4], Z = [z1, z2, z3, z4], W = [w1, w2, w3, w4]
        // output = [x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4]

        // Output: [x1, y1, z1, w1]
        Packed a = z.interleave_hi(x); // A: [x1, z1, x2, z2]
        Packed b = w.interleave_hi(y); // A: [y1, w1, y2, w2]
        write(b.interleave_hi(a));

        // Output: [x2, y2, z2, w2]
        write(b.interleave_lo(a));

        // Output: [x3, y3, z3, w3]
        Packed c = z.interleave_lo(x); // A: [x3, z3, x4, z4]
        Packed d = w.interleave_lo(y); // A: [y3, w3, y4, w4]
        write(d.interleave_hi(c));

        // Output: [x4, y4, z4, w4]
        write(d.interleave_lo(c));

        length += 16;
    }

     const float* operator() (unsigned int& length) const
    {
         length = index;
         return stream;
    }
};

#endif // HAMMER_ENGINE_STREAMPOOL__H_
