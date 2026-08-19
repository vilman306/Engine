#include "client/core/Scene.hpp"
#include "common/core/Config.hpp"

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
    m_Renderer.reset(renderer);
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
    BeginDrawing();

    // Call Draw on all client components
    for (auto& [id, object] : m_World.GetObjects())
    {
        for (const std::unique_ptr<SceneComponent>& clientComponent : object->GetSceneComponents())
        {
            clientComponent->Draw();
        }
    }

    EndDrawing();
}
