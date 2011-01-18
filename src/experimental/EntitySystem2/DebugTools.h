#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

// Standard exceptions
#include <stdexcept>

// Compile-time type constraints on classes
#include "TypeConstraints.h"

// Runtime assertion
#include <cassert>
#include <assert.h>

// Static (compile time) assertion
//#define static_assert(pred) switch(0){case 0:case pred:;}
template<int,typename MSG> struct static_assert_type { enum { Value}; typedef int Type;};
template<typename MSG> struct static_assert_type <true,MSG> {};
#define static_assert(pred) static_assert_type<pred, struct ERROR___Static_assertion_failure>

// Safe object dereferencing
#ifdef NDEBUG
#define assert_not_null(ptr) (ptr)
#define deref(obj) (obj)
#define deref_iter(iter,obj) (*(iter))
#else
#include <sstream>
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
#define assert_not_null(ptr) DEBUGTOOLS_ASSERT_DEREF((ptr),0,ptr != NULL,"assert_not_null")

// Dereferencing a pointer, assert its validity
#define deref(obj) DEBUGTOOLS_ASSERT_DEREF((obj),0,obj != NULL,"deref")

// Dereferencing an iterator, assert its validity
#define deref_iter(iter,obj) (*DEBUGTOOLS_ASSERT_DEREF((iter),((obj).end()),obj; iter != obj.end(),"deref iterator"))

#endif

#endif // DEBUGTOOLS_H
