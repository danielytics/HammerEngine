
#include <vector>
#include <SDL.h>

#include "Profiler.h"
#include "Messenger.h"

#include <iostream>

int logicThread (void* data)
{
    profile("logicThread");
    Messenger& messenger = *(reinterpret_cast<Messenger*>(data));

    unsigned next = 1;

    std::vector<bool> flags;
    flags.push_back(true);
    SceneNode* scene = 0; // SceneNode's should be cache aligned, as they will be shared accross processor itnerconnect - use a cache alligned chunked memory pool.

    volatile bool& running = messenger.running(); // Should be cached locally (but not in register!) until main thread sets it to false, in which case it is loaded accross the interconnect bus
    while (running)
    {
        // Run controllers
        /*
         Update all "inteligent" agents, that is, the player and AI agents. Controllers should be parallelized.
         */

        // Run physics
        /*
         Update every game object in parallel. This should apply cotnroller actions, physics, collision handling, etc.
         */

        // Pre-render
        /*
         Here we want to basically figure out what needs to be drawn and in what order so it can be pre-sorted before the renderer thread
         sends it to the graphics card for drawing. We want to do as much of the CPU-bound rendering work as possible here so that
         it can be parallelized. The renderer thread should then simply walk the sorted render list and send commands to the GPU.
         */
        scene = (SceneNode*)next++;
        // Build scene ...
        flags.push_back(false);

        // Give scene to renderer and take previous one, if any.
        scene = const_cast<SceneNode*>(messenger.getAndSetScene(scene));
        if (scene)
        {
            flags[(unsigned int)scene] = true;
            //sceneNodePool.release(scene);
        }
    }
    scene = 0; // Make sure the last scene isn't passed in twice.
    while ((scene = const_cast<SceneNode*>(messenger.getAndSetScene(scene))) != 0)
    {
        //sceneNodePool.release(scene);
        flags[(unsigned int)scene] = true;
        scene = 0;
        SDL_Delay(1); // Give other thread time to pass new scene back.
    }

    int count = 0;
    int index = 0;
    for (std::vector<bool>::iterator i=flags.begin(); i!=flags.end(); i++)
    {
        if (*i != true)
        {
            count++;
            std::clog << "Not released: " << index << "\n";
        }
        index++;
    }
    std::clog << "Number of scenes not released: " << count << "\n";

    return 0;
}

