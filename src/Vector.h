#ifndef VECTOR_H
#define VECTOR_H

// SSE and SSE2 intrinsics
#include <xmmintrin.h>
#include <emmintrin.h>

typedef __m128 float4;

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
    float length ();

    // Normalize vector
    void normalize ();

    // Normalize four vectors
    static void normalize (Vector& v1, Vector& v2, Vector& v3, Vector& v4);

};

#endif // VECTOR_H
