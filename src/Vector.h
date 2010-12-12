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

typedef __m128 vec4f;
struct __attribute__((packed, aligned(16))) float4
{
    float x, y, z, w;
};

typedef float (Vector::*FPTR_DotProduct) (const Vector& other) const;

#define float4_x(f4) (((float *)&(f4))[0])
#define float4_y(f4) (((float *)&(f4))[1])
#define float4_z(f4) (((float *)&(f4))[2])
#define float4_w(f4) (((float *)&(f4))[3])

class Vector
{
private:
    // vec4f vectors are treated as 4D vectors
    float4 components;

    float dotProduct_SSE2 (const Vector& other) const;
    WITH_SSE3(float dotProduct_SSE3 (const Vector& other) const);
    static FPTR_DotProduct fptr_dotProduct;

public:
    Vector ();
    Vector (const float x, const float y=0, const float z=0, const float w=0);
    Vector (const vec4f vec);
    Vector (const Vector& other);

    // Get vector components
    inline float x () const {return float4_x(components);}
    inline float y () const {return float4_y(components);}
    inline float z () const {return float4_z(components);}
    inline float w () const {return float4_w(components);}

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
