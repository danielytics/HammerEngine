#ifndef VECTOR_H
#define VECTOR_H

// SSE, SSE2 and SSE3 intrinsics
#ifdef __SSE3__
#include <pmmintrin.h>
#define WITH_SSE3(x) x
#else
#include <emmintrin.h>
#define WITH_SSE3(x)
#endif

class Vector;

typedef __m128 float4;
typedef float (Vector::*FPTR_DotProduct) (const Vector& other) const;

class Vector
{
private:
    // All vectors are treated as 4D vectors
    union
    {
        float4 components;
        struct
        {
            float cX, cY, cZ, cW;
        };
    };

    float dotProduct_SSE2 (const Vector& other) const;
    WITH_SSE3(float dotProduct_SSE3 (const Vector& other) const);
    static FPTR_DotProduct fptr_dotProduct;

public:
    Vector ();
    Vector (const float x, const float y=0, const float z=0, const float w=0);
    Vector (const float4 vec);
    Vector (const Vector& other);

    // Get vector components
    inline float x () const {return cX;}
    inline float y () const {return cX;}
    inline float z () const {return cY;}
    inline float w () const {return cZ;}

    // Find the vectors modulus
    float length () const;

    // Normalize vector
    void normalize ();

    // Dot product
    inline float dotProduct (const Vector& other) const {return (this->*fptr_dotProduct)(other);}

    /** Vectorized versions which operate on four vectors at one: */

    // Normalize four vectors
    static void normalize (Vector& v1, Vector& v2, Vector& v3, Vector& v4);


    static void init ();
};

#endif // VECTOR_H
