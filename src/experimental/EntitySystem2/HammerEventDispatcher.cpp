
#include "HammerEventDispatcher.h"

/********************************************************************
 * Event object implementation
 *******************************************************************/

EventImpl::EventImpl (const std::string& t, const std::string& m)
    : Event ()
    , properties(0)
    , m_type(t)
    , m_mailbox(m)
{

}

EventImpl::~EventImpl ()
{
    if (properties)
    {
        delete properties;
    }
}

Attribute& EventImpl::operator() (std::string property)
{
    if (properties == 0)
    {
        // Create only when accessed
        properties = new std::map<std::string, Attribute>();
    }
    return (*properties)[property];
}

const std::string& EventImpl::type () const
{
    return m_type;
}

const std::string& EventImpl::mailbox () const
{
    return m_mailbox;
}

/********************************************************************
 * Dispatcher implementation
 *******************************************************************/

Event& HammerEventDispatcher::createEvent (const std::string& type, const std::string& mailbox)
{
    tbb::concurrent_vector<EventImpl>::iterator iter = eventDispatchQueue.push_back(EventImpl(type, mailbox));
    return *iter;
}

HammerEventDispatcher::HammerEventDispatcher ()
{

}

HammerEventDispatcher::~HammerEventDispatcher ()
{

}

const tbb::concurrent_vector<EventImpl>& HammerEventDispatcher::getEvents () const
{
    return eventDispatchQueue;
}

void HammerEventDispatcher::disposeEvents ()
{
    eventDispatchQueue.clear();
    eventDispatchQueue.shrink_to_fit();
}

