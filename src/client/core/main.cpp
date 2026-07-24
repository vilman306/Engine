#include "client/core/ClientGame.hpp"
#include "common/core/Config.hpp"
#include "common/core/EngineRegistry.hpp"

int main()
{
    Config::SetupPaths();

    EngineRegistry::RegisterSceneComponents();

    ClientGame game;
    game.Run();
    return 0;
}
