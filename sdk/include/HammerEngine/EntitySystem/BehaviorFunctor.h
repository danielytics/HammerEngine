#ifndef HAMMER_ENGINE_SYSTEMFUNCTOR__H_
#define HAMMER_ENGINE_SYSTEMFUNCTOR__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "Entity.h"

/**
  * BehaviorFunctor
  *
  * Base class for functors to run as a traits behavior function.
  */
class BehaviorFunctor
{
public:
    virtual void operator() (const Entity& entity, const Trait& in, Trait& out)=0;
};

/**
  * BehaviorFunctorWrapper<T1>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking a single templated input trait.
  */
template <class T1>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking two templated input traits.
  */
template <class T1, class T2>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking three templated input traits.
  */
template <class T1, class T2, class T3>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3, T4>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking four templated input traits.
  */
template <class T1, class T2, class T3, class T4>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), entity<T4>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3, T4, T5>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking five templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), entity<T4>(), entity<T5>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking six templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), entity<T4>(), entity<T5>(), entity<T6>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6, T7>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking seven templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), entity<T4>(), entity<T5>(), entity<T6>(), entity<T7>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6, T7, T8>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking eight templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), entity<T4>(), entity<T5>(), entity<T6>(), entity<T7>(), entity<T8>(), static_cast<T1>(out));
    }
};

/**
  * BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6, T7, T8, T9>
  *
  * Templated implementation of BehaviorFunctor.
  * Implement BehaviorFunctor for a behavior function taking nine templated input traits.
  */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
class BehaviorFunctorWrapper : public BehaviorFunctor
{
private:
    typedef void (*FuncPtr) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&, T1&);
    FuncPtr function;

public:
    BehaviorFunctorWrapper (FuncPtr fptr) : function(fptr) {}
    ~BehaviorFunctorWrapper () {}

    void operator() (const Entity entity, const Trait& in, Trait& out)
    {
        function(static_cast<T1>(in), entity<T2>(), entity<T3>(), entity<T4>(), entity<T5>(), entity<T6>(), entity<T7>(), entity<T8>(), entity<T9>(), static_cast<T1>(out));
    }
};

#endif // HAMMER_ENGINE_SYSTEMFUNCTOR__H_
