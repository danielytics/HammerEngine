#include "Info.h"
#include "Logger.h"

#include <SDL.h>

Info::Info()
{
    numProcessors = SDL_GetCPUCount();
}

int Info::numberOfProcessors () const
{
    return numProcessors;
}

bool Info::hasMMX () const
{
    return SDL_HasMMX();
}

bool Info::has3DNow () const
{
    return SDL_Has3DNow();
}

bool Info::hasSSE () const
{
    return SDL_HasSSE();
}

bool Info::hasSSE2 () const
{
    return SDL_HasSSE2();
}

void Info::writeToLog (Logger* logger) const
{
    logger->write(Logger::INFO,
                  LogStream() << " +----------"                                      "\n"
                                 " | CPU Details"                                    "\n"
                                 " +----------"                                      "\n"
                                 " | Processors: " << numProcessors               << "\n"
                                 " | MMX:        " << (hasMMX()   ? "yes" : "no") << "\n"
                                 " | 3DNow:      " << (has3DNow() ? "yes" : "no") << "\n"
                                 " | SSE:        " << (hasSSE()   ? "yes" : "no") << "\n"
                                 " | SSE2:       " << (hasSSE2()  ? "yes" : "no") << "\n"
                                 " +----------"                                      "\n");
}
