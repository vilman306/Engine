#ifndef SCENECOMPONENT_HPP
#define SCENECOMPONENT_HPP

#include "common/core/Component.hpp"

class GameObject;

class SceneComponent : public Component
{
public:
    SceneComponent();
    virtual ~SceneComponent();

    virtual void Update(double dt) = 0;
    virtual void Draw() = 0;
};

#endif // SCENECOMPONENT_HPP
