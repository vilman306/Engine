#include "server/core/ServerGame.hpp"
#include "common/core/Config.hpp"
#include "common/core/EngineRegistry.hpp"

#define SERVER

int main()
{
    Config::SetupPaths();

    EngineRegistry::RegisterSceneComponents();

    ServerGame game;
    game.Run();
    return 0;
}
