#include "client/core/Scene.hpp"
#include <raylib-cpp.hpp>
#include "common/core/Config.hpp"

Scene::Scene(World& p_World) : world(p_World)
{
    // NOTE: Do NOT use the World here; it has not yet been initialized/constructed!
    Window.Init(Config::WindowWidth, Config::WindowHeight, Config::WindowTitle);
}

Scene::~Scene()
{
    //dtor
}

void Scene::Update(double dt)
{
    // Call Update on all client components
    for (auto& [id, object] : world.GetObjects()) {
        for (const std::unique_ptr<SceneComponent>& clientComponent : object->GetSceneComponents()) {
            clientComponent->Update(dt);
        }
    }
}

void Scene::Draw()
{
    BeginDrawing();

    // Call Draw on all client components
    for (auto& [id, object] : world.GetObjects()) {
        for (const std::unique_ptr<SceneComponent>& clientComponent : object->GetSceneComponents()) {
            clientComponent->Draw();
        }
    }

    EndDrawing();
}
