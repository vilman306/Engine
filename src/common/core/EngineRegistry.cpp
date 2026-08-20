#include "common/core/EngineRegistry.hpp"
#include <stdexcept>

#ifdef CLIENT
// Used to register SceneComponents so that they can be added via their names
std::unordered_map< std::string, std::function< std::unique_ptr<SceneComponent>() > > EngineRegistry::SceneComponents;

#include "client/components/SpriteRenderer.hpp"
void EngineRegistry::RegisterSceneComponents()
{
    if (!EngineRegistry::SceneRenderer) {
        throw std::runtime_error("Tried to construct a SpriteRenderer without the EngineRegistry having a reference to the SDL_Renderer.");
    }
    EngineRegistry::SceneComponents["SpriteRenderer"] = []() {
        return std::make_unique<SpriteRenderer>(EngineRegistry::SceneRenderer);
    };
}

void EngineRegistry::SetRenderer(SDL_Renderer* renderer)
{
    EngineRegistry::SceneRenderer = renderer;
}
#endif
