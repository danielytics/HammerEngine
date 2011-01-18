#ifndef HAMMER_ENGINE_TYPECONSTRAINTS__H_
#define HAMMER_ENGINE_TYPECONSTRAINTS__H_

/**
  * Compile-time type-hierarchy assertions.
  * Author: Bjarne Stroustrup http://www2.research.att.com/~bs/bs_faq2.html#constraints
  */

namespace TypeConstraints {

    /**
      * T is derived from B
      */
    template<class T, class B> struct Derived_from {
        static void constraints(T* p) { B* pb = p; }
        Derived_from() { void(*p)(T*) = constraints; }
    };

    /**
      * B can be assigned to T
      * (actually the same thing as Derived_from - both exist so that the intent is clear)
      */
    template<class T, class B> struct Can_assign {
        static void constraints(T* p) { B* pb = p; }
        Can_assign() { void(*p)(T*) = constraints; }
    };

    /**
      * T2 can be copied to T1
      */
    template<class T1, class T2> struct Can_copy {
        static void constraints(T1 a, T2 b) { T2 c = a; b = a; }
        Can_copy() { void(*p)(T1,T2) = constraints; }
    };

    /**
      * T1 can be compared to T2
      */
    template<class T1, class T2 = T1> struct Can_compare {
        static void constraints(T1 a, T2 b) { a==b; a!=b; a<b; }
        Can_compare() { void(*p)(T1,T2) = constraints; }
    };
};

#endif // HAMMER_ENGINE_TYPECONSTRAINTS__H_
