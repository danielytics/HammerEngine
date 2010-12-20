#include "Messenger.h"

Messenger::Messenger (bool* r) :
        runningFlag(r)
{
}

bool* Messenger::running ()
{
    return runningFlag;
}
