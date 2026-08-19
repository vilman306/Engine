#define CLIENT
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include "client/core/ClientGame.hpp"
#include "common/core/Config.hpp"
#include "common/core/EngineRegistry.hpp"
#include <stdexcept>
#include <iostream>


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    Config::SetupPaths();

    EngineRegistry::RegisterSceneComponents();

    ClientGame* game = new ClientGame();
    *appstate = game;

    try {
        SDL_SetAppMetadata(Config::WindowTitle, NULL, NULL);
        if (!game->GetScene().IsValid())
            throw std::runtime_error("Failure when initializing Scene.");
    }
    catch (const std::exception& e) {

        std::cout << "ERROR: " << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    ClientGame* game = static_cast<ClientGame*>(appstate);
    delete game;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    ClientGame* game = static_cast<ClientGame*>(appstate);
    game->Update();
    return SDL_APP_CONTINUE;
}

