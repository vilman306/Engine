#include "client/core/ClientGame.hpp"
#include "common/core/Config.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

ClientGame::ClientGame() : scene(world)
{

}

ClientGame::~ClientGame()
{
    //dtor
}

void ClientGame::Run()
{
    while (!scene.Window.ShouldClose()) {
        double time = GetTime();
        static double prevTime = time;
        double deltaTime = time - prevTime;

        scene.Update(deltaTime);
        scene.Draw();
    }
}
