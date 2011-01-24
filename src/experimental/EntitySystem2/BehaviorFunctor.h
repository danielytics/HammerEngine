#ifndef HAMMER_ENGINE_BEHAVIORFUNCTOR__H_
#define HAMMER_ENGINE_BEHAVIORFUNCTOR__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "Entity.h"
#include "SimdMacros.h"
#include "DebugTools.h"

#include <iostream>

/**
  * BehaviorFunctor
  *
  * Base class for functors to run as a traits behavior function.
  */
class BehaviorFunctor
{
public:
    virtual ~BehaviorFunctor () {}
    virtual void operator() (const ReadOnlyEntity& entity) const=0;
};

// PASS ENTITY TO BEHAVIOR

/**
  * BehaviorFunctorWrapper1<T1>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking a single templated input trait.
  */
template <class T1>
class BehaviorFunctorWrapper1 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper1 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper1 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1;
        if (entity.canGetTrait<T1>(t1))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper2<T1, T2>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking two templated input traits.
  */
template <class T1, class T2>
class BehaviorFunctorWrapper2 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper2 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper2 () {}

//    void prefetch (const ReadOnlyEntity& entity)
//    {
//        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2))
//        {
//#if defined(__SSE__) && defined(PERFORM_PREFETCH)
//            _mm_prefetch(reinterpret_cast<const char*>(t1), PREFETCH_HINT);
//            _mm_prefetch(reinterpret_cast<const char*>(t2), PREFETCH_HINT);
//#endif
//            process = true;
//        } else
//        {
//            process = false;
//        }
//    }

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }

};

/**
  * BehaviorFunctorWrapper3<T1, T2, T3>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking three templated input traits.
  */
template <class T1, class T2, class T3>
class BehaviorFunctorWrapper3 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper3 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper3 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper4<T1, T2, T3, T4>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking four templated input traits.
  */
template <class T1, class T2, class T3, class T4>
class BehaviorFunctorWrapper4 : public BehaviorFunctor
{
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper4 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper4 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, *t4, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper5<T1, T2, T3, T4, T5>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking five templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5>
class BehaviorFunctorWrapper5 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper5 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper5 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, *t4, *t5, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper6<T1, T2, T3, T4, T5, T6>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking six templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6>
class BehaviorFunctorWrapper6 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper6 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper6 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper7<T1, T2, T3, T4, T5, T6, T7>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking seven templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
class BehaviorFunctorWrapper7 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper7 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper7 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, *t7, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper8<T1, T2, T3, T4, T5, T6, T7, T8>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking eight templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
class BehaviorFunctorWrapper8 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper8 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper8 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper9<T1, T2, T3, T4, T5, T6, T7, T8, T9>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking nine templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
class BehaviorFunctorWrapper9 : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper9 (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper9 () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8; T9* t9;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8) && entity.canGetTrait<T9>(t9))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

// DO NOT PASS ENTITY TO BEHAVIOR

/**
  * BehaviorFunctorWrapper1<T1>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking a single templated input trait.
  */
template <class T1>
class BehaviorFunctorWrapper1NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper1NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper1NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1;
        if (entity.canGetTrait<T1>(t1))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper2<T1, T2>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking two templated input traits.
  */
template <class T1, class T2>
class BehaviorFunctorWrapper2NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper2NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper2NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper3<T1, T2, T3>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking three templated input traits.
  */
template <class T1, class T2, class T3>
class BehaviorFunctorWrapper3NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper3NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper3NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper4<T1, T2, T3, T4>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking four templated input traits.
  */
template <class T1, class T2, class T3, class T4>
class BehaviorFunctorWrapper4NE : public BehaviorFunctor
{
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper4NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper4NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, *t4, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper5<T1, T2, T3, T4, T5>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking five templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5>
class BehaviorFunctorWrapper5NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper5NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper5NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, *t4, *t5, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper6<T1, T2, T3, T4, T5, T6>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking six templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6>
class BehaviorFunctorWrapper6NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper6NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper6NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, *t4, *t5, *t6, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper7<T1, T2, T3, T4, T5, T6, T7>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking seven templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
class BehaviorFunctorWrapper7NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper7NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper7NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, *t4, *t5, *t6, *t7, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper8<T1, T2, T3, T4, T5, T6, T7, T8>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking eight templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
class BehaviorFunctorWrapper8NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper8NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper8NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

/**
  * BehaviorFunctorWrapper9<T1, T2, T3, T4, T5, T6, T7, T8, T9>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking nine templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
class BehaviorFunctorWrapper9NE : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&, T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper9NE (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper9NE () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8; T9* t9;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8) && entity.canGetTrait<T9>(t9))
        {
            ALIGNED(T1 out);
            assert_align(&out, 16);
            function(*t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, out);
            *t1 = out; // TODO: Delay this until later.
        }
    }
};

// DO NOT PASS OUTPUT TO BEHAVIOR

/**
  * BehaviorFunctorWrapper1<T1>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking a single templated input trait.
  */
template <class T1>
class BehaviorFunctorWrapper1NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper1NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper1NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1;
        if (entity.canGetTrait<T1>(t1))
        {
            function(entity, *t1);
        }
    }
};

/**
  * BehaviorFunctorWrapper2<T1, T2>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking two templated input traits.
  */
template <class T1, class T2>
class BehaviorFunctorWrapper2NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper2NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper2NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2))
        {
            function(entity, *t1, *t2);
        }
    }
};

/**
  * BehaviorFunctorWrapper3<T1, T2, T3>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking three templated input traits.
  */
template <class T1, class T2, class T3>
class BehaviorFunctorWrapper3NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper3NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper3NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3))
        {
            function(entity, *t1, *t2, *t3);
        }
    }
};

/**
  * BehaviorFunctorWrapper4<T1, T2, T3, T4>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking four templated input traits.
  */
template <class T1, class T2, class T3, class T4>
class BehaviorFunctorWrapper4NO : public BehaviorFunctor
{
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper4NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper4NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4))
        {
            function(entity, *t1, *t2, *t3, *t4);
        }
    }
};

/**
  * BehaviorFunctorWrapper5<T1, T2, T3, T4, T5>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking five templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5>
class BehaviorFunctorWrapper5NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper5NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper5NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5))
        {
            function(entity, *t1, *t2, *t3, *t4, *t5);
        }
    }
};

/**
  * BehaviorFunctorWrapper6<T1, T2, T3, T4, T5, T6>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking six templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6>
class BehaviorFunctorWrapper6NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper6NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper6NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6))
        {
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6);
        }
    }
};

/**
  * BehaviorFunctorWrapper7<T1, T2, T3, T4, T5, T6, T7>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking seven templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
class BehaviorFunctorWrapper7NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper7NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper7NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7))
        {
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, *t7);
        }
    }
};

/**
  * BehaviorFunctorWrapper8<T1, T2, T3, T4, T5, T6, T7, T8>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking eight templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
class BehaviorFunctorWrapper8NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper8NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper8NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8))
        {
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8);
        }
    }
};

/**
  * BehaviorFunctorWrapper9<T1, T2, T3, T4, T5, T6, T7, T8, T9>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking nine templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
class BehaviorFunctorWrapper9NO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper9NO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper9NO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8; T9* t9;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8) && entity.canGetTrait<T9>(t9))
        {
            function(entity, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9);
        }
    }
};


// DO NOT PASS ENTITY OR OUTPUT TO BEHAVIOR

/**
  * BehaviorFunctorWrapper1<T1>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking a single templated input trait.
  */
template <class T1>
class BehaviorFunctorWrapper1NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper1NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper1NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1;
        if (entity.canGetTrait<T1>(t1))
        {
            function(*t1);
        }
    }
};

/**
  * BehaviorFunctorWrapper2<T1, T2>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking two templated input traits.
  */
template <class T1, class T2>
class BehaviorFunctorWrapper2NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper2NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper2NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2))
        {
            function(*t1, *t2);
        }
    }
};

/**
  * BehaviorFunctorWrapper3<T1, T2, T3>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking three templated input traits.
  */
template <class T1, class T2, class T3>
class BehaviorFunctorWrapper3NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper3NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper3NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3))
        {
            function(*t1, *t2, *t3);
        }
    }
};

/**
  * BehaviorFunctorWrapper4<T1, T2, T3, T4>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking four templated input traits.
  */
template <class T1, class T2, class T3, class T4>
class BehaviorFunctorWrapper4NENO : public BehaviorFunctor
{
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper4NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper4NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4))
        {
            function(*t1, *t2, *t3, *t4);
        }
    }
};

/**
  * BehaviorFunctorWrapper5<T1, T2, T3, T4, T5>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking five templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5>
class BehaviorFunctorWrapper5NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper5NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper5NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5))
        {
            function(*t1, *t2, *t3, *t4, *t5);
        }
    }
};

/**
  * BehaviorFunctorWrapper6<T1, T2, T3, T4, T5, T6>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking six templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6>
class BehaviorFunctorWrapper6NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper6NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper6NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6))
        {
            function(*t1, *t2, *t3, *t4, *t5, *t6);
        }
    }
};

/**
  * BehaviorFunctorWrapper7<T1, T2, T3, T4, T5, T6, T7>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking seven templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
class BehaviorFunctorWrapper7NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper7NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper7NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7))
        {
            function(*t1, *t2, *t3, *t4, *t5, *t6, *t7);
        }
    }
};

/**
  * BehaviorFunctorWrapper8<T1, T2, T3, T4, T5, T6, T7, T8>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking eight templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
class BehaviorFunctorWrapper8NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper8NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper8NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8))
        {
            function(*t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8);
        }
    }
};

/**
  * BehaviorFunctorWrapper9<T1, T2, T3, T4, T5, T6, T7, T8, T9>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking nine templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
class BehaviorFunctorWrapper9NENO : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&);
    const FuncPtr function;

public:
    BehaviorFunctorWrapper9NENO (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper9NENO () {}

    void operator() (const ReadOnlyEntity& entity) const
    {
        T1* t1; T2* t2; T3* t3; T4* t4; T5* t5; T6* t6; T7* t7; T8* t8; T9* t9;
        if (entity.canGetTrait<T1>(t1) && entity.canGetTrait<T2>(t2) && entity.canGetTrait<T3>(t3) && entity.canGetTrait<T4>(t4) && entity.canGetTrait<T5>(t5) && entity.canGetTrait<T6>(t6) && entity.canGetTrait<T7>(t7) && entity.canGetTrait<T8>(t8) && entity.canGetTrait<T9>(t9))
        {
            function(*t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9);
        }
    }
};

#endif // HAMMER_ENGINE_BEHAVIORFUNCTOR__H_
