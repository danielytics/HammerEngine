#include "Info.h"
#include "Logger.h"

/**************************************************************************************************
 * Code "borrowed" from SDL_cpuinfo.c
 *************************************************************************************************/

#include <SDL_stdinc.h>

#if defined(__GNUC__) && defined(i386)
#define cpuid(func, a, b, c, d) \
    __asm__ __volatile__ ( \
"        pushl %%ebx        \n" \
"        cpuid              \n" \
"        movl %%ebx, %%esi  \n" \
"        popl %%ebx         \n" : \
            "=a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (func))
#elif defined(__GNUC__) && defined(__x86_64__)
#define cpuid(func, a, b, c, d) \
    __asm__ __volatile__ ( \
"        pushq %%rbx        \n" \
"        cpuid              \n" \
"        movq %%rbx, %%rsi  \n" \
"        popq %%rbx         \n" : \
            "=a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (func))
#elif (defined(_MSC_VER) && defined(_M_IX86)) || defined(__WATCOMC__)
#define cpuid(func, a, b, c, d) \
    __asm { \
        __asm mov eax, func \
        __asm cpuid \
        __asm mov a, eax \
        __asm mov b, ebx \
        __asm mov c, ecx \
        __asm mov d, edx \
    }
#else
#define cpuid(func, a, b, c, d) \
    a = b = c = d = 0
#endif

static const char *
SDL_GetCPUType()
{
    static char SDL_CPUType[48];

    if (!SDL_CPUType[0]) {
        int i = 0;
        unsigned int a, b, c, d;

        cpuid(0x80000000, a, b, c, d);
        if (a >= 0x80000004) {
            cpuid(0x80000002, a, b, c, d);
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            cpuid(0x80000003, a, b, c, d);
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            cpuid(0x80000004, a, b, c, d);
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(a & 0xff); a >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(b & 0xff); b >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(c & 0xff); c >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
            SDL_CPUType[i++] = (char)(d & 0xff); d >>= 8;
        }
        if (!SDL_CPUType[0]) {
            SDL_strlcpy(SDL_CPUType, "Unknown", sizeof(SDL_CPUType));
        }
    }
    return SDL_CPUType;
}


/*************************************************************************************************/


#include <SDL.h>

#include <iostream>

Info::Info()
{
    numProcessors = SDL_GetCPUCount();
    flagMMX = SDL_HasMMX();
    flag3DNow = SDL_Has3DNow();
    flagSSE = SDL_HasSSE();
    flagSSE2 = SDL_HasSSE2();

    int eax, ebx, ecx, edx;
    cpuid(0x0000001, eax, ebx, ecx, edx);
    flagSSE3 = (ecx & 0x1);
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
              " | Processor:    " << SDL_GetCPUType()               << "\n"
              " | CPU Count:    " << numProcessors                  << "\n"
              " | MMX:          " << (hasMMX()   ? "yes" : "no")    << "\n"
              " | 3DNow:        " << (has3DNow() ? "yes" : "no")    << "\n"
              " | SSE:          " << (hasSSE()   ? "yes" : "no")    << "\n"
              " | SSE2:         " << (hasSSE2()  ? "yes" : "no")    << "\n"
              " | SSE3:         " << (hasSSE3()  ? "yes" : "no")    << "\n"
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
