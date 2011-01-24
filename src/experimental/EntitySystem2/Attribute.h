#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Trait.h"
#include <string>
#include <sstream>

enum AttributeDataType
{
    TypeNumber = 0,
    TypeTrait,
    TypeString
};

class Attribute
{
private:
    AttributeDataType dataType;
    union
    {
        struct
        {
            unsigned int id;
            AbstractTrait::Type ptr;
        };
        float number;
    };
    std::string string;

    inline std::string typeName (const AttributeDataType t) const
    {
        if (dataType == TypeNumber)
        {
            return "number";
        }
        else if (dataType == TypeString)
        {
            return "string";
        }
        else if (dataType == TypeTrait)
        {
            return "trait";
        }
        return "UNKNOWN";
    }

    inline void typeCheck (const AttributeDataType expected) const throw (std::logic_error)
    {
        if (dataType != TypeTrait) {
            // Error, type mismatch
            std::ostringstream sstr;
            sstr << "EventAttribute Type Mismatch [expected: " << typeName(expected) << ", got " << typeName(dataType) << "]";
            throw std::logic_error(sstr.str());
        }
    }

public:
    inline void operator= (const float num)
    {
        if (dataType ==  TypeString)
        {
            string.clear();
        }
        dataType = TypeNumber;
        number = num;
    }

    inline void operator= (const std::string& str)
    {
        dataType = TypeString;
        string = str;
    }

    template<class T> inline void operator= (const T& trait)
    {
        if (dataType ==  TypeString)
        {
            string.clear();
        }
        dataType = TypeTrait;
        id = Trait<T>::id();
        ptr = AbstractTrait::from_ptr(&trait);
    }

    inline AttributeDataType type () const
    {
        return dataType;
    }

    template <class T> T& get ();
};


template <class T> inline T& Attribute::get ()
{
    typeCheck(TypeTrait);
    if (id != Trait<T>::id())
    {
        // Error, id mismatch
        std::ostringstream sstr;
        sstr << "EventAttribute Trait Mismatch [expected: " << Trait<T>::id() << ", got " << id << "]";
        throw std::logic_error(sstr.str());
    }
    return *deref(AbstractTrait::to_ptr<T>(ptr));
}
template <> inline std::string& Attribute::get<std::string> ()
{
    typeCheck(TypeString);
    return string;
}
template <> inline float& Attribute::get<float> ()
{
    typeCheck(TypeNumber);
    return number;
}
template <> inline int& Attribute::get<int> ();

#endif // ATTRIBUTE_H
