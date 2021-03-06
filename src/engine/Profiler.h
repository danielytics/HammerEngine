#ifndef PROFILER_H
#define PROFILER_H

#ifdef PROFILER_ENABLED

#define profile(name) Profiler profile_obj___((name));

#else

#define profile(name)

#endif

#include <tbb/tick_count.h>

class ProfileData;
class Profiler
{
    const char* blockName;
    tbb::tick_count startTime;

public:
    Profiler (const char* name);
    ~Profiler ();

    static void init ();
    static void term (const char* filename);

};

#endif // PROFILER_H
