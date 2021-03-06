
#include <vector>
#include <SDL.h>

#include <tbb/pipeline.h>
#include <tbb/concurrent_queue.h>

#include "Profiler.h"
#include "Messenger.h"

#include <iostream>

class GameObject;

class ControllerFilter : public tbb::filter
{
private:
    void* operator() (void* item)
    {
        GameObject* object = static_cast<GameObject*>(item);

    }
};

int logicThread (void* data)
{
    profile("logicThread");
    {
        Messenger& messenger = *(reinterpret_cast<Messenger*>(data));
        MemoryPool sceneNodePool; // Memory pool for renderable scene nodes
        tbb::concurrent_bounded_queue<SceneNode*> sceneNodeQueue;

        // Create pipeline and filters
        tbb::pipeline pipeline;
        ScatterWork scatter(sceneNodePool);
        ControllerFilter controllers;
        PhysicsFilter physics;
        PreRenderFilter preRender(sceneNodeQueue);

        // Set up the pipeline
        pipeline.add_filer(controllers);
        pipeline.add_filter(physics);
        pipeline.add_filter(preRender);

        SceneNode* scene = 0; // SceneNode's should be cache aligned, as they will be shared accross processor interconnect - use a cache alligned chunked memory pool

        volatile bool& running = *(messenger.running()); // Should be cached locally (but not in register!) until main thread sets it to false, in which case it is loaded across the interconnect bus causing the cached version to be reloaded
        do
        {
            // Run the pipeline
            pipeline.run(20);

            scene = 0;
            if (sceneNodeQueue.try_pop(scene))
            {
                SceneNode* next;
                while (sceneNodeQueue.try_pop(next))
                {
                    preRenderCallback(next, scene); // Generally, should add next to scene
                }
            }

            // Give scene to renderer and take previous one, if any
            scene = const_cast<SceneNode*>(messenger.getAndSetScene(scene));
            if (scene)
            {
                //sceneNodePool.release(scene);
            }
        } while (running);

        // Release resources used by pipeline
        pipeline.clear();

        // Clean up any remaining scene resources
        scene = 0; // Make sure the last scene isn't passed in twice
        while ((scene = const_cast<SceneNode*>(messenger.getAndSetScene(scene))) != 0)
        {
            //sceneNodePool.release(scene);
            scene = 0;
            SDL_Delay(1); // Give other thread time to pass new scene back
        }
    }
}

//int logicThread (void* data)
//{
//    profile("logicThread");
//    Messenger& messenger = *(reinterpret_cast<Messenger*>(data));

//    unsigned next = 1;

//    std::vector<bool> flags;
//    flags.push_back(true);
//    SceneNode* scene = 0; // SceneNode's should be cache aligned, as they will be shared accross processor interconnect - use a cache alligned chunked memory pool.

//    volatile bool& running = messenger.running(); // Should be cached locally (but not in register!) until main thread sets it to false, in which case it is loaded accross the interconnect bus
//    while (running)
//    {
//        // Run controllers
//        /*
//         Update all "inteligent" agents, that is, the player and AI agents. Controllers should be parallelized.
//         */

//        // Run physics
//        /*
//         Update every game object in parallel. This should apply cotnroller actions, physics, collision handling, etc.
//         */

//        // Pre-render
//        /*
//         Here we want to basically figure out what needs to be drawn and in what order so it can be pre-sorted before the renderer thread
//         sends it to the graphics card for drawing. We want to do as much of the CPU-bound rendering work as possible here so that
//         it can be parallelized. The renderer thread should then simply walk the sorted render list and send commands to the GPU.
//         */
//        scene = (SceneNode*)next++;
//        // Build scene ...
//        flags.push_back(false);

//        // Give scene to renderer and take previous one, if any.
//        scene = const_cast<SceneNode*>(messenger.getAndSetScene(scene));
//        if (scene)
//        {
//            flags[(unsigned int)scene] = true;
//            //sceneNodePool.release(scene);
//        }
//    }
//    scene = 0; // Make sure the last scene isn't passed in twice.
//    while ((scene = const_cast<SceneNode*>(messenger.getAndSetScene(scene))) != 0)
//    {
//        //sceneNodePool.release(scene);
//        flags[(unsigned int)scene] = true;
//        scene = 0;
//        SDL_Delay(1); // Give other thread time to pass new scene back.
//    }

//    int count = 0;
//    int index = 0;
//    for (std::vector<bool>::iterator i=flags.begin(); i!=flags.end(); i++)
//    {
//        if (*i != true)
//        {
//            count++;
//            std::clog << "Not released: " << index << "\n";
//        }
//        index++;
//    }
//    std::clog << "Number of scenes not released: " << count << "\n";

//    return 0;
//}

