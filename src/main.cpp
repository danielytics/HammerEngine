
#include "Graphics.h"
#include "Profiler.h"

#include <iostream>

#define FRAMERATE_COUNTER_LATENCY 500

int logicThread (void* data)
{
    volatile bool& running = *((bool*)data); // Should be cached locally (but not in register!) until main thread sets it to false, in which case it is loaded accross the interconnect bus
    while (running)
    {
        profile("#logicThread/main_loop");

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
        //SDL_Delay(250);
    }

    return 0;
}

int main (int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not init SDL\n";
        return -1;
    }
    Profiler::init();

    {
        profile("#main");

        bool threadInited = false;
        {
            Graphics graphics("Norse Game");

            bool threadRunning = true; // Running flag shared accross processor cores
            SDL_Thread* logic = SDL_CreateThread(logicThread, &threadRunning );
            threadInited = true;

            SDL_Event event;
            bool running = true; // Local running flag to avoid hitting the core interconnect every frame

            unsigned int frameTimer;
            unsigned int elapsedTime;
            unsigned int frames = 0;
            float framerate = 0;
            float total = 0;
            unsigned int numFrames = 0;

            try {
                //graphics.init(512, 512, false);
                graphics.init(1024, 768, false);

                frameTimer = SDL_GetTicks();

                // Run input/rendering loop
                while (running)
                {
                    profile("#main/main_loop");

                    // Get input events.
                    while(SDL_PollEvent(&event))
                    {
                        profile("#main/event_loop");

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
                            // Window event received
                            {
                                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                                // Window close butten pressed
                                {
                                    running = false;
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    graphics.render();

                    // Calculate frame rate (number of "frames" rendered to the screen per second; game logic runs unsynchronized with the renderer)
                    ++frames;
                    elapsedTime = SDL_GetTicks() - frameTimer;
                    if (elapsedTime > FRAMERATE_COUNTER_LATENCY)
                    {
                        framerate = (float)(1000 / elapsedTime) * (float)(frames);
                        frames = 0;
                        total += framerate;
                        numFrames++;
                        frameTimer = SDL_GetTicks();
                    }
                }
            }
            catch (const std::string& error)
            {
                std::cerr << "Game terminated with error: " << error << "\n";
            }

            // Terminate logic thread
            if (threadInited)
            {
                threadRunning  = false; // Share running flag accross interconnect to other thread
                int status;
                SDL_WaitThread(logic, &status);
            }

            std::cout << "Average framerate: " << (total / numFrames) << "\n";
        }
    }

    Profiler::term("performance_profile.csv");
    SDL_Quit();

    return 0;
}
