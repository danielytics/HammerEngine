
#include "Graphics.h"
#include "Profiler.h"
#include "Info.h"
#include "Logger.h"
#include "Messenger.h"

#include <iostream>

#include "Vector.h"

#define FRAMERATE_COUNTER_LATENCY 500

int logicThread (void* data);

int main (int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not init SDL\n";
        return -1;
    }
    Profiler::init();
    Vector::init();

    Vector v1(3.0f, 4.0f, 0.0f, 0.0f);
    Vector v2(1.0f, 0.0f, 0.0f, 0.0f);
    Vector v3(1.0f, 1.0f, 1.0f, 0.0f);
    Vector v4(0.0f, 0.0f, 4.0f, 3.0f);

    v1.dotProduct(v2);

    std::cout << "v1.length() = " << v1.length() << "\n";
    std::cout << "v2.length() = " << v2.length() << "\n";
    std::cout << "v3.length() = " << v3.length() << "\n";
    std::cout << "v4.length() = " << v4.length() << "\n";

    Vector::normalize(v1, v2, v3, v4);
    std::cout << "\n";
    std::cout << "v1.length() = " << v1.length() << "\n";
    std::cout << "v2.length() = " << v2.length() << "\n";
    std::cout << "v3.length() = " << v3.length() << "\n";
    std::cout << "v4.length() = " << v4.length() << "\n";

    {
        profile("main");

        bool threadInited = false;
        {
            Graphics graphics("Norse Game");

            bool threadRunning = true; // Running flag shared accross processor cores
            Messenger messenger(threadRunning);
            messenger.getAndSetScene(0);

            SDL_Thread* logic = SDL_CreateThread(logicThread, &messenger );
            threadInited = true;

            SDL_Event event;
            bool running = true; // Local running flag to avoid hitting the core interconnect every frame

            unsigned int frameTimer;
            unsigned int elapsedTime;
            unsigned int frames = 0;
            float framerate = 0;
            float total = 0;
            unsigned int numFrames = 0;

            // Pointer to next scene to render.
            const SceneNode* scene = 0;

            try {
                //graphics.init(512, 512, false);
                graphics.init(1024, 768, false);

                frameTimer = SDL_GetTicks();

                // Run input/rendering loop
                {
                    Logger logger;
                    Info info;
                    info.writeToLog(&logger);

                    profile("main_loop");
                    while (running)
                    {
                        // Get input events.
                        {
                            profile("event_loop");
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
                        }
                        // Take next scene and give back old scene.
                        scene = messenger.getAndSetScene(scene);
                        if (scene != 0)
                        {
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
                        else
                        {
                            // If no scene to render, give other threads more time.
                            SDL_Delay(1);
                        }
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
                // Shut down logic threrad.
                threadRunning  = false; // Share running flag accross interconnect to other thread
                int status;
                while ((scene = messenger.getAndSetScene(scene)) != 0)
                {
                    SDL_Delay(1); // Give the logic thread time to release scene.
                }

                SDL_WaitThread(logic, &status);
            }

            std::cout << "Average framerate: " << (total / numFrames) << "\n";
        }
    }

    Profiler::term("performance_profile.csv");
    SDL_Quit();

    return 0;
}
