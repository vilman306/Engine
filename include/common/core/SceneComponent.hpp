#ifndef SCENECOMPONENT_HPP
#define SCENECOMPONENT_HPP

#include "common/core/Component.hpp"
#include <SDL3/SDL_render.h>

class GameObject;

class SceneComponent : public Component
{
public:
    SceneComponent(SDL_Renderer* renderer) : m_Renderer(renderer) {};
    virtual ~SceneComponent();

    virtual void Update(double dt) = 0;
    virtual void Draw() = 0;

protected:
    SDL_Renderer* m_Renderer;
};

#endif // SCENECOMPONENT_HPP
