#ifndef HAMMER_ENGINE_TRAIT__H_
#define HAMMER_ENGINE_TRAIT__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "Resource/Handle.h"

/**
  * Trait
  *
  * Interface for all traits.
  * All traits have an ID and either a resource handle or one or more floating point parameters.
  */
class Trait
{
public:
    virtual ~Trait () {}

    virtual unsigned int getId ()=0;
    virtual float& get (unsigned int index) const=0;
    virtual Handle& handle () const=0;
};


/**
  * TraitBase
  *
  * Implements the Trait interface with default implementations.
  * Templated on the derived class so that the ID can be statically accessed.
  *
  * Use:
  *    class MyTrait : public TraitBase<MyTrait> {
  *        public:
  *            static const unsigned int id = EntitySystem::registerTrait(<number of parameters here>);
  *    };
  */
template <class T> class TraitBase : public Trait
{
private:
    union {
        float* data;
        Handle resource;
    };

public:
    TraitBase ()
    {

    }
    virtual ~TraitBase () {}

    float& get (unsigned int index) const
    {
        return data[index];
    }

    Handle& handle () const
    {
        return resource;
    }

    unsigned int getId ()
    {
        return T::id;
    }
};

#endif // HAMMER_ENGINE_TRAIT__H_
