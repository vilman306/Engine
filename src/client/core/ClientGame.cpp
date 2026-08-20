#include "client/core/ClientGame.hpp"
#include <SDL3/SDL_timer.h>

ClientGame::ClientGame() : m_Scene(m_World)
{

}

ClientGame::~ClientGame()
{
    //dtor
}

//void ClientGame::Run()
//{
//    while (!m_Scene.Window.ShouldClose()) {
//        double time = GetTime();
//        static double prevTime = time;
//        double deltaTime = time - prevTime;
//
//        m_Scene.Update(deltaTime);
//        m_Scene.Draw();
//    }
//}

void ClientGame::Update()
{
    double currentTime = static_cast<double>(SDL_GetPerformanceCounter()) / SDL_GetPerformanceCounter();
    static double previousTime = currentTime;

    double deltaTime = currentTime - previousTime;

    m_Scene.Update(deltaTime);
    m_Scene.Draw();

    previousTime = currentTime;
}
