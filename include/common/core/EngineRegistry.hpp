#ifndef ENGINEREGISTRY_HPP_INCLUDED
#define ENGINEREGISTRY_HPP_INCLUDED


#include <memory>
#include <functional>
#include "common/core/SceneComponent.hpp"
#include <string>
#include <unordered_map>

namespace EngineRegistry
{
    // Used to register SceneComponents so that they can be added from their names
    extern std::unordered_map< std::string, std::function< std::unique_ptr<SceneComponent>() > > SceneComponents;
    void RegisterSceneComponents();
}

#endif // ENGINEREGISTRY_HPP_INCLUDED
