#ifndef HAMMER_ENGINE_PACKED__H_
#define HAMMER_ENGINE_PACKED__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

// SSE, SSE2 and SSE3 intrinsics
#ifdef __SSE3__
#include <pmmintrin.h>
#define WITH_SSE3(x) x
#else
#include <emmintrin.h>
#define WITH_SSE3(x)
#endif

typedef __m128 vecf;
//typedef __m128i veci;
typedef float scalar;

#define SIMD_NUM 4

// Only on GCC, on windows, on functions using SSE
#if defined(__GNUC__) && defined(_WIN32)
#define SSECALL         __attribute__((force_align_arg_pointer))
#else
#define SSECALL
#endif

/*
 * Compiler specific attributes:
 *  ALIGN_16            Data is aligned on a 16-byte boundary (requirement for fast SSE loads/stores)
 *  RESTRICTED_PTR      Pointer is "restricted", meaning that for the scope of the pointer, the target of the pointer will only be accessed through that pointer (and pointers copied from it)
 *
 */
#ifdef __GNUC__
#define ALIGN_16        __attribute__((__aligned__ (16)))
#define RESTRICTED_PTR  __restrict__
#define ALIGNED(x)      x ALIGN_16
#else
#define ALIGN_16        __declspec(align(16))
#define RESTRICTED_PTR  __declspec(restrict) /*__restrict*/
#define ALIGNED(x)      ALIGN_16 x
#endif

namespace simd {

    /**
      * Packed
      *
      * Class for performing SIMD operations on packed single precision floating point numbers.
      *
      */
    class Packed
    {
    private:
        vecf item;

    public:
        Packed (vecf itm) : item(itm) {}
        Packed (const Packed& itm) : item(itm.item) {}
        Packed (const float xx, const float yy, const float zz, const float ww)
        {
            item = _mm_set_ps(ww, zz, yy, xx);
        }

        /* Vector operations */

        /**
          * Add lhs and rhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs + rhs
          */
        inline static Packed add (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_add_ps(lhs.item, rhs.item);
        }

        /**
          * Subtract rhs from lhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs - rhs
          */
        inline static Packed sub (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_sub_ps(lhs.item, rhs.item);
        }

        /**
          * Multiply lhs and rhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs * rhs
          */
        inline static Packed mul (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_mul_ps(lhs.item, rhs.item);
        }

        /**
          * Divide rhs by lhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs / rhs
          * WARNING:    Division is always SLOW, multiply by reciprocal instead if possible
          */
        inline static Packed div (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_div_ps(lhs.item, rhs.item);
        }

        /**
          * Calculate square root of v
          * Params:
          *     v       A packed float vector
          * Returns:    A packed float vector, sqrt(v)
          */
        inline static Packed sqrt (const Packed& RESTRICTED_PTR v)
        {
            return _mm_sqrt_ps(v.item);
        }

        /**
          * Calculate reciprocal square root of v
          * Params:
          *     v       A packed float vector
          * Returns:    A packed float vector, 1 / sqrt(v)
          */
        inline static Packed rsqrt (const Packed& RESTRICTED_PTR v)
        {
            return _mm_rsqrt_ps(v.item);
        }

        /**
          * Calculate minimum of either lhs and rhs
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs < rhs ? lhs : rhs
          */
        inline static Packed min (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_min_ps(lhs.item, rhs.item);
        }

        /**
          * Calculate maximum of either lhs and rhs
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs > rhs ? lhs : rhs
          */
        inline static Packed max (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_min_ps(lhs.item, rhs.item);
        }

        /**
          * Calculate the inverse of v
          * Params:
          *     v       A packed float vector
          * Returns:    A packed float vector, 1 / v
          */
        inline static Packed inverse (const Packed& RESTRICTED_PTR v)
        {
            return _mm_rcp_ps(v.item);
        }

        /**
          * Perform lhs bitwise and rhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs & rhs
          */
        inline static Packed band (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_and_ps(lhs.item, rhs.item);
        }

        /**
          * Perform lhs bitwise or rhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs | rhs
          */
        inline static Packed bor (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_or_ps(lhs.item, rhs.item);
        }

        /**
          * Perform lhs bitwise xor rhs.
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs ^ rhs
          */
        inline static Packed bxor (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_xor_ps(lhs.item, rhs.item);
        }

        /**
          * Perform lhs bitwise and (bitwise not rhs).
          * Params:
          *     lhs     A packed float vector
          *     rhs     A packed float vector
          * Returns:    A packed float vector, lhs & ~rhs
          */
        inline static Packed bandnot (const Packed& RESTRICTED_PTR lhs, const Packed& RESTRICTED_PTR rhs)
        {
            return _mm_andnot_ps(lhs.item, rhs.item);
        }

        /* Overloaded Operators, for convenience only - speed critical code paths should prefer the static functions */
    #ifndef PACKED_NO_OPERATORS
        inline Packed operator+ (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::add(*this, other);
        }
        inline Packed operator- (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::sub(*this, other);
        }
        inline Packed operator* (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::mul(*this, other);
        }
        inline Packed operator/ (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::div(*this, other);
        }
        inline Packed operator& (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::band(*this, other);
        }
        inline Packed operator| (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::bor (*this, other);
        }
        inline Packed operator^ (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            return Packed::bxor(*this, other);
        }
        inline Packed get_sqrt () const
        {
            return Packed::sqrt(*this);
        }
        inline Packed get_rsqrt () const
        {
            return Packed::rsqrt(*this);
        }
    #endif

        template <int N> inline float v () const
        {
            float result;
            _mm_store_ss(&result, _mm_shuffle_ps(item, item, _MM_SHUFFLE(N, N, N, N)));
            return result;
        }
        inline float v0 () const {return v<0>();}
        inline float v1 () const {return v<1>();}
        inline float v2 () const {return v<2>();}
        inline float v3 () const {return v<3>();}
        inline float v (const unsigned int index) const
        {
            switch (index) {
            case 0: return v<0>();
            case 1: return v<1>();
            case 2: return v<2>();
            case 3: return v<3>();
            default: return 0;
            }
        }

        inline void store (float* RESTRICTED_PTR data) RESTRICTED_PTR const
        {
            /*
             * WARNING: data MUST be 16-byte aligned!
             *
             * Store [x1, x2, x3, x4] to memory, float* ptr = {x4, x3, x2, x1}
             */
            _mm_store_ps(data, item);
        }

        template <unsigned int A, unsigned int B, unsigned int C, unsigned int D> inline Packed shuffle () RESTRICTED_PTR const
        {
            /* this = [x1, x2, x3, x4]
             *
             * dest = [this.D, this.C, this.B, this.A]
             *
             * A, B, C, D - indexed from left to right
             * dest       - written from right to left
             *
             * eg, A, B, C, D = 2, 1, 3, 0; dest = [x1, x4, x2, x3]
             */
            return _mm_shuffle_ps(item, item, _MM_SHUFFLE(A, B, C, D));
        }

        template <unsigned int A, unsigned int B, unsigned int C, unsigned int D> inline Packed shuffle (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            /* this  = [x1, x2, x3, x4]
             * other = [y1, y2, y3, y4]
             *
             * dest = [other.D, other.C, this.B, this.A]
             *
             * A, B, C, D - indexed from left to right
             * dest       - written from right to left
             *
             * eg, A, B, C, D = 0, 1, 2, 3; dest = [y4, y3, x2, x1]
             */
            return _mm_shuffle_ps(item, other.item, _MM_SHUFFLE(A, B, C, D));
        }

        inline Packed interleave_lo (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            // interleave_lo([x1, x2, x3, x4], [y1, y2, y3, y4]) = [y3, x3, y4, x4]
            return _mm_unpacklo_ps(item, other.item);
        }

        inline Packed interleave_hi (const Packed& RESTRICTED_PTR other) RESTRICTED_PTR const
        {
            // interleave_lo([x1, x2, x3, x4], [y1, y2, y3, y4]) = [y1, x1, y2, x2]
            return _mm_unpackhi_ps(item, other.item);
        }

//        inline veci to_pi () RESTRICTED_PTR const
//        {
//            return _mm_cvtps_epi32(item);
//        }

    };

} // simd

#endif // HAMMER_ENGINE_PACKED__H_
