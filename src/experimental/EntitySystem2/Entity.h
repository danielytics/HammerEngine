#ifndef HAMMER_ENGINE_ENTITY__H_
#define HAMMER_ENGINE_ENTITY__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include "EntitySystem.h"
#include "Trait.h"

#include "DebugTools.h"

#include <sstream>

class Entity
{
private:
    EntitySystem& owner;

public:
    Entity (EntitySystem& o, unsigned int ident) : owner(o), id(ident), valid(ident != (unsigned int)-1) {}
    Entity (const Entity& other) : owner(other.owner), id(other.id), valid(other.valid) {}
    virtual ~Entity () {}

    const unsigned int id;
    const bool valid;

    // Convenience functions for accessing an entities traits

    template <class T> inline T& trait () const
    {
        AbstractTrait::Type t = owner.getTrait(id, Trait<T>::id());
        if (t)
        {
            Trait<T>* tt = AbstractTrait::to_ptr<Trait<T> >(t);
            assert_align(&(deref(tt)->data), 16);
            return deref(tt)->data;
        } else
        {
            std::ostringstream sstr;
            sstr << "Entity " << (void*)id << " does not have trait " << typeid(T).name() << "!\n";
            throw std::runtime_error(sstr.str());
        }
    }

    template <class T> inline T& getTraitUnsafe () const
    {
        Trait<T>* t = AbstractTrait::to_ptr<Trait<T> >(owner.getTrait(id, Trait<T>::id()));
        assert_not_null(t);
        assert_align(&(deref(t)->data), 16);
        return deref(t)->data;
    }

    template <class T> inline bool hasTrait () const
    {
        return owner.getTrait(id, Trait<T>::id()) != 0;
    }

    template <class T> inline bool canGetTrait (T*& trait) const
    {
        AbstractTrait::Type t = owner.getTrait(id, Trait<T>::id());
        if (t)
        {
            Trait<T>* tt = AbstractTrait::to_ptr<Trait<T> >(t);
            assert_not_null(tt);
            assert_align(&(deref(tt)->data), 16);
            trait = &(deref(tt)->data);
            return true;
        }
        return false;
    }

    template <class T> inline Entity addTrait () const
    {
        owner.addTrait(id, Trait<T>::id());
        return *this;
    }

    template <class T> inline Entity removeTrait () const
    {
        owner.removeTrait(id, Trait<T>::id());
        return *this;
    }

    inline void destroy ()
    {
        owner.destroyEntity(*this);
    }

    inline EntityState state ()
    {
        return owner.getState(*this);
    }

    inline void setState (const EntityState& state)
    {
        owner.setState(*this, state);
    }

    // Entity lookup

    template <class T> static inline Entity& fromTrait (T& trait, EntitySystem* es)
    {
        Trait<T> temp(trait);
        return es->getEntityFromTrait(&temp);
    }
};

#endif // HAMMER_ENGINE_ENTITY__H_
