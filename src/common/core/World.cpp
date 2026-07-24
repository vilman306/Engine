#include "common/core/World.hpp"
//#include "client/components/SpriteRenderer.hpp"
#include "common/core/Config.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <cassert>
#include "common/core/EngineRegistry.hpp"
#include "common/core/JSONExtensions.hpp"
#include "common/core/RayMathExtensions.hpp"

World::World()
{
    LoadLevel("level_start.json");
}

World::~World()
{
    //dtor
}

void World::LoadLevel(const std::string& LevelFileName)
{
    try {
        LoadLevelImpl(LevelFileName);
    }
    catch (std::invalid_argument& e) {
        std::cout << "Failed to load level: " + LevelFileName + "\n" \
                  << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << "Failed to load level: " + LevelFileName + "\n" \
                  << e.what() << std::endl;
    }
}

void World::LoadLevelImpl(const std::string& LevelFileName)
{
    // Load the file 'assets/data/prefabs.json' and store its data
    std::ifstream prefabsFile(Config::PrefabsPath);
    if (prefabsFile.fail())
        throw std::runtime_error("ERROR: Could not open " + Config::PrefabsPath.string());
    nlohmann::json prefabsJson = JsonUtils::GetFromJson<nlohmann::json>(nlohmann::json::parse(prefabsFile), "Prefabs");

    // Load the file 'assets/data/levels/LevelFileName' and store its data
    std::filesystem::path levelPath = Config::AssetsPath / "data/levels" / LevelFileName;
    std::ifstream levelFile(levelPath);
    if (levelFile.fail())
        throw std::invalid_argument("ERROR: Could not open " + levelPath.string());
    nlohmann::json levelJson = nlohmann::json::parse(levelFile);

    // Create local storage of the level's GameObjects. This will be moved to m_GameObjects if everything succeeds.
    std::unordered_map<uint32_t, std::unique_ptr<GameObject>> levelGameObjects;

    // For each GameObject data in levelJson:
    for (const nlohmann::json& gameObjectJson : levelJson["GameObjects"])
    {
        // Get the GameObject's name
        std::string gameObjectName = JsonUtils::GetFromJson<std::string>(gameObjectJson, "Name");
        // Get the GameObject's Prefab
        std::string prefabName = JsonUtils::GetFromJson<std::string>(gameObjectJson, "Prefab");
        // Create the GameObject
        std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>();
        gameObject->Name = gameObjectName;
        // Apply transform values (position ("translation"), rotation, scale)
        nlohmann::json transformJson = JsonUtils::GetFromJson<nlohmann::json>(gameObjectJson, "Transform");
        // Position
        std::vector<float> position = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Position");
        gameObject->transform.translation = RayUtils::RaylibVector3FromStdVector(position);
        // Rotation
        std::vector<float> rotation = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Rotation");
        gameObject->transform.rotation = RayUtils::RaylibQuaternionFromStdVector(rotation);
        // Scale
        std::vector<float> scale = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Scale");
        gameObject->transform.scale = RayUtils::RaylibVector3FromStdVector(scale);
        // Get the Prefab data
        nlohmann::json prefabJson = JsonUtils::GetChildJsonFromKeyValuePair<std::string>(prefabsJson, "Name", prefabName);
        // Get the GameObject's override values for all of its SceneComponents and SimulationComponents
        nlohmann::json sceneOverridesJson = JsonUtils::GetFromJson<nlohmann::json>(gameObjectJson, "SceneComponentsOverrides");
        nlohmann::json simulationOverridesJson = JsonUtils::GetFromJson<nlohmann::json>(gameObjectJson, "SimulationComponentsOverrides");
        #ifdef CLIENT
        // Add all of the Prefab's SceneComponents to the GameObject
        for (nlohmann::json& componentJson : JsonUtils::GetFromJson<nlohmann::json>(prefabJson, "SceneComponents"))
        {
            // Create the component
            std::string componentName = JsonUtils::GetFromJson<std::string>(componentJson, "Name");
            std::unique_ptr<SceneComponent> component = EngineRegistry::SceneComponents[componentName]();
            // Apply default component values
            nlohmann::json defaultsJson = JsonUtils::GetFromJson<nlohmann::json>(componentJson, "Defaults");
            component.get()->ApplyDefaults(defaultsJson);
            // Apply component value overrides
            component.get()->ApplyOverrides(JsonUtils::GetFromJson<nlohmann::json>(sceneOverridesJson, componentName));
            // Add the component to the GameObject
            gameObject->AddSceneComponent(std::move(component));
        }
        #endif
        // Add SimulationComponents if this machine is 'Simulating'.
        #ifdef SERVER
        for (nlohmann::json& componentJson : JsonUtils::GetFromJson<nlohmann::json>(prefabJson, "SceneComponents"))
        {
            // Create the component
            std::string componentName = JsonUtils::GetFromJson<std::string>(componentJson, "Name");
            std::unique_ptr<SceneComponent> component = EngineRegistry::SceneComponents[componentName]();
            // Apply default component values
            nlohmann::json defaultsJson = JsonUtils::GetFromJson<nlohmann::json>(componentJson, "Defaults");
            component.get()->ApplyDefaults(defaultsJson);
            // Apply component value overrides
            component.get()->ApplyOverrides(JsonUtils::GetFromJson<nlohmann::json>(sceneOverridesJson, componentName));
            // Add the component to the GameObject
            gameObject->AddSceneComponent(std::move(component));
        }
        #endif

        // Add the GameObject to the local GameObject storage
        levelGameObjects.emplace(gameObject->GetID(), std::move(gameObject));
    }
    // Move local GameObject storage to m_GameObjects. (Here, all GameObjects have been successfully created.)
    m_GameObjects = std::move(levelGameObjects);
}

