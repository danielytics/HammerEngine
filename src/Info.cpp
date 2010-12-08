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
    // Get video mode details
    int refreshRate = 0;
    int width = 0, height = 0;
    SDL_DisplayMode mode;
    SDL_SelectVideoDisplay(0);
    if (SDL_GetCurrentDisplayMode(&mode) == 0)
    {
        refreshRate = mode.refresh_rate;
        width = mode.w;
        height = mode.h;
    }

    // Get power management details
    int percent = 0;
    SDL_PowerState state = SDL_GetPowerInfo(0, &percent);

    LogStream stream;
    stream << " +--------------------"                                 "\n"
              " | System Information"                                  "\n"
              " +--------------------"                                 "\n"
              " | Platform:     " << std::string(SDL_GetPlatform()) << "\n"
              " | Processors:   " << numProcessors                  << "\n"
              " | MMX:          " << (hasMMX()   ? "yes" : "no")    << "\n"
              " | 3DNow:        " << (has3DNow() ? "yes" : "no")    << "\n"
              " | SSE:          " << (hasSSE()   ? "yes" : "no")    << "\n"
              " | SSE2:         " << (hasSSE2()  ? "yes" : "no")    << "\n"
              " | Display:      " << width << "x" << height << " " << refreshRate << "Hz\n"
              " | Video Driver: " << SDL_GetVideoDriver(0)          << "\n"
              " | Battery:      ";
    if (state != SDL_POWERSTATE_NO_BATTERY)
    {
        stream << std::string(state != SDL_POWERSTATE_ON_BATTERY ? "Charging, " : "") << percent << "%\n";
    }
    else
    {
        stream << "No Battery\n";
    }
    stream << " +--------------------\n";
    logger->write(Logger::LOG_INFO, stream);

}
