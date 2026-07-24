#include "common/core/EngineRegistry.hpp"

#ifdef CLIENT
#include "client/components/SpriteRenderer.hpp"
#endif

// Used to register SceneComponents so that they can be added from their names

std::unordered_map< std::string, std::function< std::unique_ptr<SceneComponent>() > > EngineRegistry::SceneComponents;

void EngineRegistry::RegisterSceneComponents()
{
    #ifdef CLIENT
    EngineRegistry::SceneComponents["SpriteRenderer"] = []() {
        return std::make_unique<SpriteRenderer>();
    };
    #endif
}
