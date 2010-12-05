
#include "Renderer.h"


#include <iostream>

int logicThread (void* data)
{
    volatile bool& running = *((bool*)data); // Should be cached locally (but not in register!) until main thread sets it to false, in which case it is loaded accross the interconnect bus
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
    }

    return 0;
}

int main (int argc, char** argv)
{
    Renderer renderer("Norse Game");

    bool threadRunning = true; // Running flag shared accross processor cores
    SDL_Thread* logic = SDL_CreateThread(logicThread, &threadRunning );

    SDL_Event event;
    bool running = true; // Local running flag to avoid hitting the core interconnect every frame

    try {
        renderer.init(512, 512, false);

        // Run input/rendering loop
        while (running)
        {
            // Get input events.
            while(SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    // Key was pushed
                    {
                        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        {
                            running = false;
                        }
                        /*
                        Input events should be translated to commands and dispatched to the Player Controller.
                        */
                    }
                    break;
                case SDL_KEYUP:
                    // Key was released
                    break;
                case SDL_WINDOWEVENT:
                    // Window close butten pressed
                    {
                        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        {
                            running = false;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            renderer.render();
        }
    }
    catch (const std::string& error)
    {
        std::cerr << "Game terminated with error: " << error << "\n";
    }

    // Terminate logic thread
    threadRunning  = false; // Share running flag accross interconnect to other thread
    int status;
    SDL_WaitThread(logic, &status);

    return 0;
}
