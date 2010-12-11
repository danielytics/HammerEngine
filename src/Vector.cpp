#include "Vector.h"
#include "Info.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

#define elementInVector(vec, slot) (((float *)&((vec)))[(slot)])
#define toScalar(vec) elementInVector((vec), X)
#define shuffleTo(vec, slot) _mm_shuffle_ps((vec), (vec), _MM_SHUFFLE((slot), (slot), (slot), (slot)))
#define makeVector(xx,yy,zz,ww) _mm_set_ps((ww), (zz), (yy), (xx)) // Packing is done in reverse

Vector::Vector()
{
    components = _mm_setzero_ps();
}

Vector::Vector (const float x, const float y, const float z, const float w)
{
    components = makeVector(x, y, z, w);
}

Vector::Vector (const float4 vec) :
        components(vec)
{

}

Vector::Vector (const Vector& other)
{
    // Copy the vectors components.
    components = other.components;
}

#include <cmath>
#include <iostream>

float Vector::length () const
{   // result = sqrt(sqr(cX) + sqr(cY) + sqr(cZ) + sqr(cW))

    // Square the vectors components, x,y,z,w = sqr(cX),sqr(cY),sqr(cZ),sqr(cW)
    float4 squares = _mm_mul_ps(components, components);

    // horizontal add
    float4 temp = _mm_add_ps(squares, _mm_shuffle_ps(squares, squares, _MM_SHUFFLE(X, Y, Z, W))); // a, b, c, d = (x+w), (y+z), (z+y), (w+x)
    float4 added = _mm_add_ss(_mm_shuffle_ps(temp, temp, _MM_SHUFFLE(X, X, X, X)),  // a +
                              _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(Y, Y, Y, Y))); // b

    // sqrt(added)
    float4 result = _mm_sqrt_ss(added);
    return toScalar(result);
}

// Normalize the vector; if multiple vectors need to be normalized, use Vector::normalize(v1,v2,v3,v4) instead for ~4x speedup
void Vector::normalize ()
{   // Multiply components by reciprocal square root of the sum of squares of components
    // recip = rsqrt(sqr(cX) + sqr(cY) + sqr(cZ) + sqr(cW))
    // result = recip*cX,recip*cY,recip*cZ,recip*cW

    // Square the vectors components, x,y,z,w = sqr(cX),sqr(cY),sqr(cZ),sqr(cW)
    float4 squares = _mm_mul_ps(components, components);

    // horizontal add
    float4 temp = _mm_add_ps(squares, _mm_shuffle_ps(squares, squares, _MM_SHUFFLE(X, Y, Z, W))); // a, b, c, d = (x+w), (y+z), (z+y), (w+x)
    float4 added = _mm_add_ss(_mm_shuffle_ps(temp, temp, _MM_SHUFFLE(X, X, X, X)),  // a +
                              _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(Y, Y, Y, Y))); // b

    // 1 / sqrt(added)
    float4 reciprocalLength = _mm_rsqrt_ss(added);
    components = _mm_mul_ps(components, shuffleTo(reciprocalLength, X));
}

// Calculate the dot product of the vector; if the dot product of multiple vectors needs to be found, use Vector::dotProduct(v1,v2,v3,v4) instead for ~4x speedup
float Vector::dotProduct_SSE2 (const Vector& other) const
{
    std::cout << "SSE2 dot product\n";
    return 0;
}

#ifdef __SSE3__
float Vector::dotProduct_SSE3 (const Vector& other) const
{
    std::cout << "SSE3 dot product\n";
    float4 temp1 = _mm_mul_ps(components, other.components);
    float4 temp2 = _mm_hadd_ps(temp1, temp1);
    float4 temp3 = _mm_hadd_ps(temp2, temp2);
    float result;
    _mm_store_ss(&result, temp3);
    return result;
}
#endif

// Normalize four vectors at once
void Vector::normalize (Vector& v1, Vector& v2, Vector& v3, Vector& v4)
{   // Multiply components by reciprocal square root of the sum of squares of components
    // recip = rsqrt(sqr(cX) + sqr(cY) + sqr(cZ) + sqr(cW))
    // result = recip*cX,recip*cY,recip*cZ,recip*cW

    // Get the components from the vectors
    float4 xVals = makeVector(v1.cX, v2.cX, v3.cX, v4.cX);
    float4 yVals = makeVector(v1.cY, v2.cY, v3.cY, v4.cY);
    float4 zVals = makeVector(v1.cZ, v2.cZ, v3.cZ, v4.cZ);
    float4 wVals = makeVector(v1.cW, v2.cW, v3.cW, v4.cW);

    // Squares
    float4 squareX = _mm_mul_ps(xVals, xVals);
    float4 squareY = _mm_mul_ps(yVals, yVals);
    float4 squareZ = _mm_mul_ps(zVals, zVals);
    float4 squareW = _mm_mul_ps(wVals, wVals);

    // Add all components together
    float4 added = _mm_add_ps(_mm_add_ps(squareX, squareY),
                              _mm_add_ps(squareZ, squareW));

    // 1 / sqrt(added)
    float4 rsrt = _mm_rsqrt_ps(added);

    // Multiply components by reciprocal and store back to vectors
    v1.components = _mm_mul_ps(v1.components, shuffleTo(rsrt, X));
    v2.components = _mm_mul_ps(v2.components, shuffleTo(rsrt, Y));
    v3.components = _mm_mul_ps(v3.components, shuffleTo(rsrt, Z));
    v4.components = _mm_mul_ps(v4.components, shuffleTo(rsrt, W));
}

FPTR_DotProduct Vector::fptr_dotProduct = 0;
void Vector::init ()
{
    Info info;
#ifdef __SSE3__
    // If we have SSE3 available, use SSE3 optimized functions
    if (info.hasSSE3())
    {
        fptr_dotProduct = &Vector::dotProduct_SSE3;
    }
    // Otherwise fall back to SSE2
    else
#endif
    {
        fptr_dotProduct = &Vector::dotProduct_SSE2;
    }
}
