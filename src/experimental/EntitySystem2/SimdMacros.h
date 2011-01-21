#ifndef SIMDMACROS_H
#define SIMDMACROS_H

#if !defined(__SSE__) && defined(_M_IX86_FP) && _M_IX86_FP>=1
#define __SSE__
#endif

// Cannot compile without SSE, so make sure it is available
#ifndef __SSE__
#error "SSE not available, cannot compile without SSE"
#endif

// Include intrinsics
#include <xmmintrin.h>

#ifdef PERFORM_PREFETCH
#define PREFETCH_HINT _MM_HINT_NTA
#endif

// GCC and MSCV compatible alignment and restricted pointer macros
#ifdef __GNUC__
#define ALIGN_16        __attribute__((__aligned__ (16)))
#define RESTRICTED_PTR  __restrict__
#define ALIGNED(x)      x ALIGN_16
#else
#define ALIGN_16        __declspec(align(16))
#define RESTRICTED_PTR  __declspec(restrict) /*__restrict*/
#define ALIGNED(x)      ALIGN_16 x
#endif

#endif // SIMDMACROS_H
