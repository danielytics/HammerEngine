#ifndef RENDERER_H
#define RENDERER_H

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <SDL.h>

#include <string>

class Graphics
{
private:
    bool inited;
    const std::string gameName;
    SDL_WindowID window;
    SDL_GLContext context;

    unsigned int startTime;

public:
    Graphics (const std::string& name);
    ~Graphics ();

    void init (unsigned int width, unsigned int height, bool fullscreen, bool vsync=true);
    void term ();
    void render ();
};

#endif // RENDERER_H
