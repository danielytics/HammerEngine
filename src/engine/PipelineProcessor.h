#ifndef PIPELINEPROCESSOR_H
#define PIPELINEPROCESSOR_H


// SSE, SSE2 and SSE3 intrinsics
#ifdef __SSE3__
#include <pmmintrin.h>
#define WITH_SSE3(x) x
#else
#include <emmintrin.h>
#define WITH_SSE3(x)
#endif

#include <tbb/concurrent_queue.h>

typedef __m128 vec4f;

class Vec4f
{
private:
    vec4f item;

public:
    Vec4f (vec4f& itm) : item(itm) {}
    Vec4f (Vec4f& itm) : item(itm.item) {}

    inline Vec4f operator+ (Vec4f& __restrict__ other) const
    {
        return _mm_add_ps(item, other.item);
    }
    inline Vec4f operator- (Vec4f& __restrict__ other) const
    {
        return _mm_sub_ps(item, other.item);
    }
    inline Vec4f operator* (Vec4f& __restrict__ other) const
    {
        return _mm_sub_ps(item, other.item);
    }
    inline Vec4f operator/ (Vec4f& __restrict__ other) const
    {
        return _mm_sub_ps(item, other.item);
    }
};

class PackedValue
{
public:
    float* elements;
    unsigned int numElements;

    static void unpack (float* const __restrict__ elements, vec4f* __restrict__ vec, const unsigned int index, const unsigned int numElements)
    {
        for (unsigned int i = numElements; i; --i)
        {
            ((float*)vec++)[index] = *(elements++);
        }
    }
    /*
     PackedValue a, b, c, d;
     const int numElementsPerVector = 5;
     vec4f* vecs = new vec4f[numElementsPerVector];
     PackedValue::unpack(a.elements, vecs, 3, numElementsPerVector);
     PackedValue::unpack(b.elements, vecs, 2, numElementsPerVector);
     PackedValue::unpack(c.elements, vecs, 1, numElementsPerVector);
     PackedValue::unpack(d.elements, vecs, 0, numElementsPerVector);

     // Extract components for {x, y, angle, dx, dy}
     vec4f& x     = vecs[0];
     vec4f& y     = vecs[1];
     vec4f& angle = vecs[2];
     vec4f& dx    = vecs[3];
     vec4f& dy    = vecs[4];

     // Compute new position: {x', y'} = {x + dx, y + dy}
     vec4f newX = _mm_add_ps(x, dx);
     vec4f newY = _mm_add_ps(y, dy);

     ...

     PackedValue na, nb, nc, nd;

     PackedValue::pack(na.elements, vecs, 3, numElementsPerVector);
     PackedValue::pack(nb.elements, vecs, 2, numElementsPerVector);
     PackedValue::pack(nc.elements, vecs, 1, numElementsPerVector);
     PackedValue::pack(nd.elements, vecs, 0, numElementsPerVector);

     // na.x => a.x + d.dx; nb => b.x + b.dx; ...
     */
};

class PipelineProcessor
{
private:
    tbb::concurrent_queue<PackedValue> dataInQueue;
    tbb::concurrent_queue<PackedValue> dataOutQueue;

    bool stopProcessing;

public:
    PipelineProcessor () :
            stopProcessing(false)
    {
    }

    void process ()
    {
        while (!stopProcessing)
        {
            for (unsigned int i=3; i; --i)
            {

            }
        }
    }

};

/*

 data -> dataInQueue
    scatter dataInQueue (unpack into groups of 4; stream out)
        process in blocks of 4
    gather dataOutQueue (pack into individual data items)
 dataOutQueue -> results

 */

#endif // PIPELINEPROCESSOR_H
