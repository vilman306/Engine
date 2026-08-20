#include "client/core/Scene.hpp"
#include "common/core/Config.hpp"
#include <SDL3/SDL_init.h>
#include "common/core/EngineRegistry.hpp"

Scene::Scene(World& p_World) : m_World(p_World)
{
    // NOTE: Do NOT use m_World here; it has not yet been initialized/constructed!

    // Create/initialize an SDL Window and Renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    try {
        if (!SDL_Init(SDL_INIT_VIDEO))
            throw std::runtime_error("Failure on SDL_Init: " + std::string(SDL_GetError()));
        if (!SDL_CreateWindowAndRenderer(Config::WindowTitle, Config::WindowWidth, Config::WindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer))
            throw std::runtime_error("Failure on SDL_CreateWindowAndRenderer: " + std::string(SDL_GetError()));
        if (!SDL_SetRenderLogicalPresentation(renderer, Config::WindowWidth, Config::WindowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX))
            throw std::runtime_error("Failure on SDL_SetRenderLogicalPresentation: " + std::string(SDL_GetError()));
    }
    catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        m_IsValid = false;
    }
    m_Window.reset(window);
    SetRenderer(renderer);
}

void Scene::SetRenderer(SDL_Renderer* renderer)
{
    m_Renderer.reset(renderer);
    EngineRegistry::SceneRenderer = renderer;
}

Scene::~Scene()
{
    //dtor
}

void Scene::Update(double dt)
{
    // Call Update on all client components
    for (auto& [id, object] : m_World.GetObjects())
    {
        for (const std::unique_ptr<SceneComponent>& clientComponent : object->GetSceneComponents())
        {
            clientComponent->Update(dt);
        }
    }
}

void Scene::Draw()
{
    // Clear
    SDL_SetRenderDrawColorFloat(m_Renderer.get(), 0.25f, 0.25f, 0.25f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(m_Renderer.get());


    // Call Draw on all client components
    for (auto& [id, object] : m_World.GetObjects())
    {
        for (const std::unique_ptr<SceneComponent>& clientComponent : object->GetSceneComponents())
        {
            clientComponent->Draw();
        }
    }

    // Draw to screen
    SDL_RenderPresent(m_Renderer.get());
}
