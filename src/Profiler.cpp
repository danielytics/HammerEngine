#include "Profiler.h"

#include <SDL.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include <iostream>

// Get an item from a map, specified by key, or val if key does not exist
template <typename K, typename V> V get(const std::map<K, V>& m, const K& key, const V& val)
{
    typename std::map<K, V>::const_iterator it = m.find(key);
    if ( it == m.end() )
    {
        return val;
    }
    else
    {
        return it->second;
    }
}

// Data structure to hold the run times, counts and child blocks of profiled code blocks
struct ProfileData
{
    ProfileData (const std::string& n) : name(n), runTime(0), runCount(0), parent(0) {}
    const std::string name;
    double runTime;
    unsigned int runCount;

    ProfileData* parent;
    std::map<std::string, ProfileData*> children;
};

// Current block in each thread
std::map<SDL_threadID, ProfileData*> current;
std::map<SDL_threadID, std::vector<ProfileData*> > roots;

SDL_mutex* lock; // Lock to ensure threads do not corrupt the data, will be under high contention, so the profiling code is not suitable for release builds

// A profiled code block has been entered
Profiler::Profiler (const char* name) :
        blockName(name),
        startTime(tbb::tick_count::now())
{
    SDL_threadID threadID = SDL_ThreadID();
    SDL_mutexP(lock); // Lock

    // Get the current block for this thread
    ProfileData* pd = get(current, threadID, (ProfileData*)0);
    ProfileData* block;
    if (pd == 0)
    {
        std::vector<ProfileData*>& rootList = roots[threadID];
        for (std::vector<ProfileData*>::iterator i = rootList.begin(); i != rootList.end(); i++)
        {
            if ((*i)->name == name)
            {
                pd = *i;
                break;
            }
        }
        if (pd == 0)
        {
            pd = new ProfileData(blockName);
            roots[threadID].push_back(pd); // Ensure the root blocks are always accessible
        }
        block = pd;
    }
    else
    {
        block = get<std::string, ProfileData*>(pd->children, name, 0);
        if (block == 0)
        {
            // If child block does not yet exist, create it and set its parent to the current block
            block = new ProfileData(blockName);
            block->parent = pd;
            pd->children[name] = block;
        }

    }

    // Increment block run count
    block->runCount++;

    // Set block as the current block
    current[threadID] = block;

    SDL_mutexV(lock); // Unlock
}

// A profiled code block has been exited
Profiler::~Profiler ()
{
    SDL_threadID threadID = SDL_ThreadID();
    SDL_mutexP(lock); // Lock

    // Get the current block for this thread
    ProfileData* pd = current[threadID];
    pd->runTime += (tbb::tick_count::now() - startTime).seconds();

    // Switch to parent block
    current[threadID] = pd->parent;

    SDL_mutexV(lock); // Unlock
}

void Profiler::init ()
{
    lock = SDL_CreateMutex();
}

void outputBlockInfo (ProfileData* pd, unsigned int depth, double totalTime, std::ofstream& file)
{
    // Indent
    for (unsigned int i = 0; i < depth; ++i)
    {
        file << "- ";
    }
    // Output profile information for this block
    file << pd->name << "," << pd->runTime << "," << pd->runCount << "," <<
            ((pd->runTime / totalTime) * 100.0f)
            << "%\n";

    // Output profile information for child blocks
    for (std::map<std::string, ProfileData*>::iterator it = pd->children.begin(); it != pd->children.end(); it++)
    {
        outputBlockInfo((*it).second, depth+1, pd->runTime, file);
    }
}

void Profiler::term (const char* filename)
{
    SDL_DestroyMutex(lock);

    std::ofstream file(filename);
    file << "Name,Time (seconds),Count,Run %\n\n";

    for (std::map<SDL_threadID, std::vector<ProfileData*> >::iterator it = roots.begin(); it != roots.end(); it++)
    {
        file << "Thread " << (*it).first << "\n";
        std::vector<ProfileData*>& rootList = (*it).second;
        for (std::vector<ProfileData*>::iterator i = rootList.begin(); i != rootList.end(); i++)
        {
            outputBlockInfo(*i, 0, (*i)->runTime, file);
        }
        file << "\n";
    }
}
