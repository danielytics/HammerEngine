#ifndef HAMMEREVENTDISPATCHER_H
#define HAMMEREVENTDISPATCHER_H

#include "EventDispatcher.h"
#include "Event.h"

#include <map>
#include <tbb/concurrent_vector.h>

class EventImpl : public Event
{
private:
    std::map<std::string, Attribute>* properties;
    const std::string m_type;
    const std::string m_mailbox;

    EventImpl (const std::string& t, const std::string& m);

public:
    virtual ~EventImpl ();

    Attribute& operator() (std::string property);
    const std::string& type () const;
    const std::string& mailbox () const;

    friend class HammerEventDispatcher;
};

class HammerEventDispatcher : public EventDispatcher
{
private:
    tbb::concurrent_vector<EventImpl> eventDispatchQueue;

    Event& createEvent (const std::string& type, const std::string& mailbox);

public:
    HammerEventDispatcher ();
    virtual ~HammerEventDispatcher ();

    const tbb::concurrent_vector<EventImpl>& getEvents () const;

    /**
      * Empty event queue and purge created event objects.
      *
      * NOT thread safe!
      */
    void disposeEvents ();
};

#endif // HAMMEREVENTDISPATCHER_H
