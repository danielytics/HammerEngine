#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

// Standard exceptions
#include <stdexcept>

// Compile-time type constraints on classes
#include "TypeConstraints.h"

// Runtime assertion
#include <cassert>

// Static (compile time) assertion
template<int,typename MSG> struct static_assert_type { enum { Value}; typedef int Type;};
template<typename MSG> struct static_assert_type <true,MSG> {};
#define compiler_assert(pred) static_assert_type<pred, struct ERROR___Static_assertion_failure>
#define compile_time_assert(pred) switch(0){case 0:case pred:;}

#ifdef NDEBUG

#define assert_not_null(ptr) ((void)0)
#define deref(obj) (obj)
#define deref_iter(iter,obj) (*(iter))
#define assert_align(ptr,align) ((void)0)

#else
#include <sstream>
#include "TemplateTools.h"
#include "Null.h"

// Safe object dereferencing
template <class T> inline T DEBUGTOOLS_assert (T obj, bool failure, const std::string& message, unsigned int line)
{
    if (failure)
    {
        std::ostringstream sstr;
        sstr << message << line;
        throw std::logic_error(sstr.str());
    }
    return obj;
}
#define DEBUGTOOLS_ASSERT_DEREF(obj,invalid,msg,caption) (DEBUGTOOLS_assert(obj, obj == invalid, "Assertion failed: " caption " (" #msg ") in " __FILE__ " on line ", __LINE__))

// Assert pointer is not null
#define assert_not_null(ptr) DEBUGTOOLS_ASSERT_DEREF((ptr),nullptr,ptr != NULL,"assert_not_null")

// Dereferencing a pointer, assert its validity
#define deref(obj) DEBUGTOOLS_ASSERT_DEREF((obj),nullptr,obj != NULL,"deref")

// Dereferencing an iterator, assert its validity
#define deref_iter(iter,obj) (*DEBUGTOOLS_ASSERT_DEREF((iter),((obj).end()),obj; iter != obj.end(),"deref iterator"))

// Alignment assertions
template <int Alignment> inline void DEBUGTOOLS_assert_align(unsigned long pointer, const char* var, const char* file, const unsigned int line)
{
    if ((pointer & AlignmentMask<Alignment>::Mask) != 0)
    {
        std::ostringstream sstr;
        sstr << "assert_align(" << var << ", " << Alignment << ") failed for address " << (void*)pointer << " in " << file << " on line " << line;
        throw std::logic_error(sstr.str());
    }
}
#define assert_align(ptr,align) DEBUGTOOLS_assert_align<align>((unsigned long)(ptr), #ptr, __FILE__, __LINE__)

#endif

#endif // DEBUGTOOLS_H
