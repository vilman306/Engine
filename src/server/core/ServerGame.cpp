#include "server/core/ServerGame.hpp"
#include "common/core/Config.hpp"
#include <iostream>

ServerGame::ServerGame()
{

}

ServerGame::~ServerGame()
{
    //dtor
}

void ServerGame::Run()
{
    while (true) { // TODO: Change condition
        double time = GetTime();
        static double prevTime = time;
        double deltaTime = time - prevTime;

        simulation.Update(deltaTime);
    }
}
