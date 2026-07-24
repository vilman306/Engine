#ifndef SIMULATIONCOMPONENT_HPP
#define SIMULATIONCOMPONENT_HPP

#include "common/core/Component.hpp"

class GameObject;

class SimulationComponent : public Component
{
public:
    SimulationComponent();
    virtual ~SimulationComponent();

    virtual void Update(double dt) = 0;

    GameObject* m_Owner;
};

#endif // SIMULATIONCOMPONENT_HPP
