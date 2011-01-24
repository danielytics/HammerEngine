#ifndef HAMMER_ENGINE_BEHAVIORBUILDER__H_
#define HAMMER_ENGINE_BEHAVIORBUILDER__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "BehaviorFunctor.h"
#include "TypeConstraints.h"
#include "Trait.h"

class BehaviorBuilder
{
private:
    EntitySystem* entitySystem;
public:
    BehaviorBuilder (EntitySystem* ngin) : entitySystem(ngin) {}
    ~BehaviorBuilder () {}

    // PASS ENTITY TO BEHAVIOR

    // One input trait
    template <class T1>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper1<T1>(func));
    }

    // Two input traits
    template <class T1, class T2>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper2<T1, T2>(func));
    }

    // Three input traits
    template <class T1, class T2, class T3>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper3<T1, T2, T3>(func));
    }

    // Fourinput traits
    template <class T1, class T2, class T3, class T4>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper4<T1, T2, T3, T4>(func));
    }

    // Five input traits
    template <class T1, class T2, class T3, class T4, class T5>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper5<T1, T2, T3, T4, T5>(func));
    }

    // Six input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper6<T1, T2, T3, T4, T5, T6>(func));
    }

    // Seven input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper7<T1, T2, T3, T4, T5, T6, T7>(func));
    }

    // Eight input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper8<T1, T2, T3, T4, T5, T6, T7, T8>(func));
    }

    // Nine input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper9<T1, T2, T3, T4, T5, T6, T7, T8, T9>(func));
    }

    // DO NOT PASS ENTITY TO BEHAVIOR

    // One input trait
    template <class T1>
    void registerBehavior(void (*func) (const T1&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper1NE<T1>(func));
    }

    // Two input traits
    template <class T1, class T2>
    void registerBehavior(void (*func) (const T1&, const T2&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper2NE<T1, T2>(func));
    }

    // Three input traits
    template <class T1, class T2, class T3>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper3NE<T1, T2, T3>(func));
    }

    // Fourinput traits
    template <class T1, class T2, class T3, class T4>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper4NE<T1, T2, T3, T4>(func));
    }

    // Five input traits
    template <class T1, class T2, class T3, class T4, class T5>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper5NE<T1, T2, T3, T4, T5>(func));
    }

    // Six input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper6NE<T1, T2, T3, T4, T5, T6>(func));
    }

    // Seven input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper7NE<T1, T2, T3, T4, T5, T6, T7>(func));
    }

    // Eight input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper8NE<T1, T2, T3, T4, T5, T6, T7, T8>(func));
    }

    // Nine input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&, T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper9NE<T1, T2, T3, T4, T5, T6, T7, T8, T9>(func));
    }

    // DO NOT PASS OUTPUT TO BEHAVIOR

    // One input trait
    template <class T1>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper1NO<T1>(func));
    }

    // Two input traits
    template <class T1, class T2>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper2NO<T1, T2>(func));
    }

    // Three input traits
    template <class T1, class T2, class T3>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper3NO<T1, T2, T3>(func));
    }

    // Fourinput traits
    template <class T1, class T2, class T3, class T4>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper4NO<T1, T2, T3, T4>(func));
    }

    // Five input traits
    template <class T1, class T2, class T3, class T4, class T5>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper5NO<T1, T2, T3, T4, T5>(func));
    }

    // Six input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper6NO<T1, T2, T3, T4, T5, T6>(func));
    }

    // Seven input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper7NO<T1, T2, T3, T4, T5, T6, T7>(func));
    }

    // Eight input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper8NO<T1, T2, T3, T4, T5, T6, T7, T8>(func));
    }

    // Nine input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    void registerBehavior(void (*func) (const ReadOnlyEntity&, const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper9NO<T1, T2, T3, T4, T5, T6, T7, T8, T9>(func));
    }

    // DO NOT PASS ENTITY OR OUTPUT TO BEHAVIOR

    // One input trait
    template <class T1>
    void registerBehavior(void (*func) (const T1&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper1NENO<T1>(func));
    }

    // Two input traits
    template <class T1, class T2>
    void registerBehavior(void (*func) (const T1&, const T2&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper2NENO<T1, T2>(func));
    }

    // Three input traits
    template <class T1, class T2, class T3>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper3NENO<T1, T2, T3>(func));
    }

    // Fourinput traits
    template <class T1, class T2, class T3, class T4>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper4NENO<T1, T2, T3, T4>(func));
    }

    // Five input traits
    template <class T1, class T2, class T3, class T4, class T5>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper5NENO<T1, T2, T3, T4, T5>(func));
    }

    // Six input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper6NENO<T1, T2, T3, T4, T5, T6>(func));
    }

    // Seven input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper7NENO<T1, T2, T3, T4, T5, T6, T7>(func));
    }

    // Eight input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper8NENO<T1, T2, T3, T4, T5, T6, T7, T8>(func));
    }

    // Nine input traits
    template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&))
    {
        entitySystem->registerBehavior(Trait<T1>::id(), new BehaviorFunctorWrapper9NENO<T1, T2, T3, T4, T5, T6, T7, T8, T9>(func));
    }
};

#endif // HAMMER_ENGINE_BEHAVIORBUILDER__H_
