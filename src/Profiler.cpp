#include "Profiler.h"

#include <SDL.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>

struct __attribute__ ((__packed__)) BlockRun
{
    unsigned int runTime;
    unsigned int timeStamp;
    unsigned int duplicates;
};

struct ProfileData
{
    ProfileData () : runTime(0), runCount(0) {}
    unsigned int runTime;
    unsigned int runCount;
    std::vector<BlockRun> runs;
};

std::map<std::string, ProfileData> blocks;
SDL_mutex* lock;

Profiler::Profiler (const char* name) :
        blockName(name),
        startTime(SDL_GetTicks())
{
}

Profiler::~Profiler ()
{
    SDL_mutexP(lock); // Lock
    // Record aggregate information
    ProfileData& pd = blocks[blockName];
    pd.runTime += (SDL_GetTicks() - startTime);
    pd.runCount++;

    if (blockName[0] != '#')
    {
        // Record single block runs
        BlockRun br;
        br.runTime = SDL_GetTicks() - startTime;
        br.timeStamp = startTime;

        if (pd.runs.size() > 0)
        {
            BlockRun& last = pd.runs.back();
            if (last.timeStamp == br.timeStamp && last.runTime == br.runTime)
            {
                last.duplicates++;
            }
            else
            {
                br.duplicates = 0;
                pd.runs.push_back(br);
            }
        }
        else
        {
            br.duplicates = 0;
            pd.runs.push_back(br);
        }
    }

    SDL_mutexV(lock); // Unlock
}

void Profiler::init ()
{
    lock = SDL_CreateMutex();
}

void Profiler::term (const char* filename)
{
    SDL_DestroyMutex(lock);

    std::ofstream file(filename);

    file << "Aggregates\n";
    file << "Code Block Name, Total Run Time, Run Count\n";
    for (std::map<std::string, ProfileData>::iterator i = blocks.begin(); i != blocks.end(); ++i)
    {
        ProfileData& pd = (*i).second;
        file << (*i).first << "," << pd.runTime << "," << pd.runCount << "\n";
    }

    file << "\nIndividual calls\n";
    file << "Code Block Name, Call Timestamp, Call Time, Duplicates\n";
    for (std::map<std::string, ProfileData>::iterator i = blocks.begin(); i != blocks.end(); ++i)
    {
        ProfileData& pd = (*i).second;
        if (pd.runs.size() > 0)
        {
            for (std::vector<BlockRun>::iterator iter = pd.runs.begin(); iter != pd.runs.end(); ++iter)
            {
                file << (*i).first << "," << (*iter).timeStamp << "," << (*iter).runTime << "," << (*iter).duplicates << "\n";
            }
        }
    }
}
