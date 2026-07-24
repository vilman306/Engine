#ifndef SCENE_H
#define SCENE_H

#include "common/core/GameObject.hpp"
#include <vector>
#include "common/core/World.hpp"

// The Scene class exists only on the client, and is what calls Draw
// and Update functions on SceneComponents (e.g. SpriteRenderer)
// attached to GameObjects in the World.

class Scene
{
public:
    Scene(World& p_World);
    ~Scene();

    // Calls Update() on all SceneComponents in the World.
    void Update(double dt);
    // Calls Draw() on all SceneComponents in the World
    void Draw();


    raylib::Window Window;

protected:

private:
    World& world;
};

#endif // SCENE_H
