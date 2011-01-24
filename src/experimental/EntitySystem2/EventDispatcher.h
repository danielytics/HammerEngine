#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <string>

#include "DebugTools.h"

class Event;

class EventDispatcher
{
private:
    static EventDispatcher* dispatcher;

    virtual Event& createEvent (const std::string& type, const std::string& mailbox)=0;

public:
    virtual ~EventDispatcher () {}

    static void implEventDispatcher (EventDispatcher* disp) {dispatcher = disp;} // Should not be used directly by user.
    inline static Event& create (const std::string& type, const std::string& mailbox) {return deref(dispatcher)->createEvent(type, mailbox);}
};

#endif // MESSAGEBUS_H
