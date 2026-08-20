#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
//#include <raylib-cpp.hpp>
#include <cstdint>
#include <memory>
#include <iostream>
#include "common/core/SceneComponent.hpp"
#include "common/core/SimulationComponent.hpp"
#include "common/components/Transform.hpp"

// A GameObject is an object that can be added to World.
// It contains data only; all logic is written in Components.

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    uint32_t GetID()
    {
        return m_ID;
    }
    // Creates and adds a new SceneComponent of type T to SceneComponents (m_SceneComponents)
    // if the GameObject does not already have one of the same type. (E.g. T = SpriteRenderer.)
    template <typename T>
    T& AddSceneComponent()
    {
        return AddComponentToContainer<SceneComponent, T>(m_SceneComponents);
    }
    // Creates and adds a new SimulationComponent of type T to SimulationComponents (m_SimulationComponents)
    // if the GameObject does not already have one of the same type.
    template <typename T>
    T& AddSimulationComponent()
    {
        return AddComponentToContainer<SimulationComponent, T>(m_SimulationComponents);
    }
    // Adds an already created SceneComponent, p_SceneComponent, to the GameObject
    // if the GameObject does not already have one of the same type.
    void AddSceneComponent(std::unique_ptr<SceneComponent> p_SceneComponent)
    {
        // Return if the GameObject already has a SceneComponent of the same type
        for (std::unique_ptr<SceneComponent>& component : m_SceneComponents)
        {
            if (typeid(component) == typeid(*p_SceneComponent.get()))
            {
                std::cout << "GameObject ' " << Name << " ' already has a SceneComponent of the same type as p_SceneComponent.\n";
                return;
            }
        }
        // Add the Component
        p_SceneComponent.get()->m_Owner = this;
        m_SceneComponents.push_back(std::move(p_SceneComponent));
    }
    // Adds an already created SimulationComponent, p_SimulationComponent, to the GameObject
    // if the GameObject does not already have one of the same type.
    void AddSimulationComponent(std::unique_ptr<SimulationComponent> p_SimulationComponent)
    {
        // Return if the GameObject already has a SimulationComponent of the same type
        for (std::unique_ptr<SimulationComponent>& component : m_SimulationComponents)
        {
            if (typeid(*component.get()) == typeid(*p_SimulationComponent.get()))
            {
                std::cout << "GameObject ' " << Name << " ' already has a SimulationComponent of the same type as p_SimulationComponent.\n";
                return;
            }
        }
        // Add the Component
        p_SimulationComponent.get()->m_Owner = this;
        m_SimulationComponents.push_back(std::move(p_SimulationComponent));
    }
    const std::vector<std::unique_ptr<SceneComponent>>& GetSceneComponents()
    {
        return m_SceneComponents;
    }
    const std::vector<std::unique_ptr<SimulationComponent>>& GetSimulationComponents()
    {
        return m_SimulationComponents;
    }

    Transform GetTransform() {return m_Transform;}
    void SetTransform(Transform p_Transform) {m_Transform = p_Transform;}
    void SetPosition(glm::vec3 position) {m_Transform.Position = position;}
    void SetRotation(glm::quat rotation) {m_Transform.Rotation = rotation;}
    void SetScale(glm::vec3 scale) {m_Transform.Scale = scale;}

    std::string Name;

private:
    // Creates and adds a new Component of type T (e.g. SpriteRenderer) to the container p_ComponentContainer
    // that stores Components with base type Base (SceneComponent or SimulationComponent).
    template <typename Base, typename T>
    T& AddComponentToContainer(std::vector<std::unique_ptr<Base>>& p_ComponentContainer)
    {
        // Make sure that a Component of type T does not already exists in p_ComponentContainer
        static_assert(std::is_base_of<Base, T>::value, "T must inherit from Base");
        for (std::unique_ptr<Base>& component : p_ComponentContainer)
        {
            if (T* existing = dynamic_cast<T*>(component.get()))
            {
                std::cout << "GameObject ' " << Name << " ' already has a " \
                          << typeid(Base).name() << " attached.\n";
                return *existing;
            }
        }
        // Create a new Component of type T and add it to p_ComponentContainer
        p_ComponentContainer.push_back(std::make_unique<T>());
        T& component = *static_cast<T*>(p_ComponentContainer.back().get());
        component.m_Owner = this;
        return component;
    }

    Transform m_Transform;
    const uint32_t m_ID;
    std::vector<std::unique_ptr<SceneComponent>> m_SceneComponents;
    std::vector<std::unique_ptr<SimulationComponent>> m_SimulationComponents;
};

#endif // GAMEOBJECT_H
