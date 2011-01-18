#ifndef HAMMER_ENGINE_TRAIT__H_
#define HAMMER_ENGINE_TRAIT__H_

#include <typeinfo>

class AbstractTrait
{
public:
    virtual ~AbstractTrait () {}

    virtual unsigned int getId () const=0;
    virtual const char* name () const=0;
};

template <class T> class Trait : public AbstractTrait
{
public:
    Trait () : data() {}
    Trait (T& d) : data(&d)
    {

    }
    virtual ~Trait () {}

    typedef T trait_type;
    T data;

    unsigned int getId () const
    {
        return id();
    }

    const char* name () const
    {
        return typeid(T).name();
    }

    static inline unsigned int id ()
    {
        static const unsigned int idnum = (unsigned int)(typeid(T).name()); // TODO: Fix This!
        return idnum;
    }
};

#endif // HAMMER_ENGINE_TRAIT__H_
