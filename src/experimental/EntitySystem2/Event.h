#ifndef EVENT_H
#define EVENT_H

#include "Trait.h"
#include "EventDispatcher.h"
#include "Attribute.h"

class Event
{
public:
    virtual ~Event () {}
    virtual Attribute& operator() (std::string property) = 0;
    virtual const std::string& type () const = 0;
    virtual const std::string& mailbox () const = 0;
};

class SendEvent
{
private:
    Event& event;

public:
    SendEvent (const std::string& type="", const std::string& mailbox="")
        : event(EventDispatcher::create(type, mailbox))
    {

    }

    inline Attribute& operator() (std::string property) const {return event(property);}
};

#endif // EVENT_H
