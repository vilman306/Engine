#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <unordered_map>
#include "common/core/GameObject.hpp"
#include <memory>
#include <filesystem>


// The World class represents a Level.
// A GameState stores all GameObjects corresponding to the Level in m_Objects.
// A Level is loaded via LoadLevel().
// (Level = a JSON with data of GameObjects.)

class World
{
public:
    World();
    virtual ~World();

    std::unordered_map<uint32_t, std::unique_ptr<GameObject>>& GetObjects()
    {
        return m_GameObjects;
    }

    GameObject* GetGameObjectByID(uint32_t ID)
    {
        auto it = m_GameObjects.find(ID);
        return (it != m_GameObjects.end()) ? it->second.get() : nullptr;
    }

    // Creates all GameObjects listed in the provided .json file
    void LoadLevel(const std::string& LevelFileName);

private:
    void LoadLevelImpl(const std::string& LevelFileName);

    std::unordered_map<uint32_t, std::unique_ptr<GameObject>> m_GameObjects;
};

#endif // GAMESTATE_H
