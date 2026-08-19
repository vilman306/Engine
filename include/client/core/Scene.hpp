#ifndef SCENE_H
#define SCENE_H

#include "common/core/World.hpp"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

// The Scene class exists only on the client, and is what calls Draw
// and Update functions on SceneComponents (e.g. SpriteRenderer)
// attached to GameObjects in the World.

// Custom deleter for m_Window
struct SDL_WindowDeleter
{
    void operator()(SDL_Window* window) const
    {
        SDL_DestroyWindow(window);
    }
};

struct SDL_RendererDeleter
{
    void operator()(SDL_Renderer* renderer) const
    {
        SDL_DestroyRenderer(renderer);
    }
};

class Scene
{
public:
    Scene(World& p_World);
    ~Scene();

    // Calls Update() on all SceneComponents in the World.
    void Update(double dt);
    // Calls Draw() on all SceneComponents in the World
    void Draw();

    bool IsValid() const { return m_IsValid; }



protected:

private:
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> m_Window;
    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> m_Renderer;
    World& m_World;
    bool m_IsValid = true; // false if something is not OK, e.g. SDL window initialization failure.
};

#endif // SCENE_H
