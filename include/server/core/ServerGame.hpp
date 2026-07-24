#ifndef GAME_H
#define GAME_H

#include "common/core/World.hpp"
#include "common/core/Simulation.hpp"

class ServerGame
{
public:
    ServerGame();
    virtual ~ServerGame();

    void Run();

    Simulation simulation;

    World world;

protected:

private:

};

#endif // GAME_H
