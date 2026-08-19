#ifndef GAME_H
#define GAME_H

#include "client/core/Scene.hpp"
#include "common/core/World.hpp"
#include "common/core/Simulation.hpp"

class ClientGame
{
public:
    ClientGame();
    virtual ~ClientGame();

    void Update();

    Scene& GetScene() { return m_Scene; }
    Simulation& GetSimulation() { return m_Simulation; }
    World& GetWorld() { return m_World; }


protected:

private:
    Scene m_Scene; // Scene must be initialized before World,
    // beause if World loads a raylib texture (to gpu), (e.g. when adding a SpriteRenderer Component),
    // a raylib window must have been initialized.

    Simulation m_Simulation;

    World m_World;

};

#endif // GAME_H
