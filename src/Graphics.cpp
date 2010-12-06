
#include "Graphics.h"
#include "Profiler.h"

Graphics::Graphics (const std::string& name) :
        inited(false),
        gameName(name),
        window(0),
        context(0)
{

}
Graphics::~Graphics ()
{
        term();
}

void Graphics::init (unsigned int width, unsigned int height, bool fullscreen, bool vsync)
{
    profile("Graphics::init");

    // Make sure there is no existing window or opengl context
    term();

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
    // Create the window
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

void Graphics::term ()
{
    if (inited)
    {
        profile("Graphics::term");

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
        inited = false;
    }
}

bool flag = false;
int state = 0;

void Graphics::render ()
{
    profile("#Graphics::render");

    unsigned int diff = SDL_GetTicks() - startTime;

    if (!flag)
    {
        if (state == 0)
        {
            glClearColor ( 1.0, 1.0, 0.0, 1.0 );
        }
        else if (state == 1)
        {
            glClearColor ( 0.0, 1.0, 0.0, 1.0 );
        }
        else if (state == 2)
        {
            glClearColor ( 0.0, 0.0, 1.0, 1.0 );
        }
        glClear ( GL_COLOR_BUFFER_BIT );
        SDL_GL_SwapWindow(window);

        flag = true;
    }
    if (diff >= 2000)
    {
        flag = false;
        state++;
        state = state > 2 ? 0 : state;
        startTime = SDL_GetTicks();
    }
}
