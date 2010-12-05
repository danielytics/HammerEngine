
#include "Renderer.h"

Renderer::Renderer (const std::string& name) :
        inited(false),
        gameName(name),
        window(0),
        context(0)
{

}
Renderer::~Renderer ()
{
    if (inited)
    {
        term();
    }
}

void Renderer::init (unsigned int width, unsigned int height, bool fullscreen, bool vsync)
{
    if (inited)
    {
        term();
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::string("Could not init SDL");
    }

    // Request an opengl 3.2 context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if (fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    // Create our window centered at 512x512 resolution
    window = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window)
    {
        SDL_Quit();
        throw std::string("Could not create window");
    }

    // Create our opengl context and attach it to the window
    context = SDL_GL_CreateContext(window);

    // This makes our buffer swap syncronized with the monitor's vertical refresh, if vsync is set to true
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);

    // Clear the colour buffer
    glClearColor ( 0.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );

    inited = true;

    startTime = SDL_GetTicks();
}

void Renderer::term ()
{
    // Terminate OpenGL
    if (context)
    {
        SDL_GL_DeleteContext(context);
    }
    // Close the window
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    // Terminate SDL
    SDL_Quit();
    inited = false;
}

void Renderer::render ()
{
    unsigned int diff = SDL_GetTicks() - startTime;
    if (diff < 2000)
    {
        glClearColor ( 1.0, 1.0, 0.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        SDL_GL_SwapWindow(window);
    }
    else if (diff < 4000)
    {
        glClearColor ( 0.0, 1.0, 0.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        SDL_GL_SwapWindow(window);
    }
    else if (diff < 6000)
    {
        glClearColor ( 0.0, 0.0, 1.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        SDL_GL_SwapWindow(window);
    }
    else
    {
        startTime = SDL_GetTicks();
    }

}
