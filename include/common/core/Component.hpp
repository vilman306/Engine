#ifndef COMPONENT_H
#define COMPONENT_H

#include <nlohmann/json.hpp>

// The Component class is the base class for Components.
// Components are what provides logic to GameObjects.

class GameObject;

class Component
{
public:
    Component();
    virtual ~Component();

    virtual void ApplyDefaults(const nlohmann::json& defaultsJson) = 0;
    virtual void ApplyOverrides(const nlohmann::json& overridesJson) = 0;
    //virtual void Update(double dt);
    //virtual void Draw();
    GameObject* m_Owner = nullptr;

//protected:
};

#endif // COMPONENT_H
