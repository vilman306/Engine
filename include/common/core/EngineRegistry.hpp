#ifndef ENGINEREGISTRY_HPP_INCLUDED
#define ENGINEREGISTRY_HPP_INCLUDED


#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include "common/core/SceneComponent.hpp"

namespace EngineRegistry
{
    #ifdef CLIENT
    // Used to register SceneComponents so that they can be added from their names
    extern std::unordered_map< std::string, std::function< std::unique_ptr<SceneComponent>() > > SceneComponents;
    void RegisterSceneComponents();

    inline SDL_Renderer* SceneRenderer = nullptr;
    void SetRenderer(SDL_Renderer* renderer);
    #endif
}

#endif // ENGINEREGISTRY_HPP_INCLUDED
