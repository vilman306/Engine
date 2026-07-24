#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include "client/core/Scene.hpp"
#include "common/core/World.hpp"
#include "common/core/Simulation.hpp"

class ClientGame
{
public:
    ClientGame();
    virtual ~ClientGame();

    void Run();

    Scene scene; // Scene must be initialized before World,
    // beause if World loads a raylib texture (to gpu), (e.g. when adding a SpriteRenderer Component),
    // a raylib window must have been initialized.

    Simulation simulation;

    World world;

protected:

private:

};

#endif // GAME_H
