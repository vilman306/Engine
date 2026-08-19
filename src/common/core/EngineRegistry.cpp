#include "common/core/EngineRegistry.hpp"

// Used to register SceneComponents so that they can be added via their names
std::unordered_map< std::string, std::function< std::unique_ptr<SceneComponent>() > > EngineRegistry::SceneComponents;

#ifdef CLIENT
#include "client/components/SpriteRenderer.hpp"
void EngineRegistry::RegisterSceneComponents()
{
    EngineRegistry::SceneComponents["SpriteRenderer"] = []() {
        return std::make_unique<SpriteRenderer>();
    };
}
#endif
