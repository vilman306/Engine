#include "common/core/Config.hpp"
#include <SDL3/SDL_filesystem.h>

std::filesystem::path Config::AssetsPath;
std::filesystem::path Config::TexturesPath;
std::filesystem::path Config::PrefabsPath;
std::filesystem::path Config::LevelsPath;


// Set up assets path etc.
void Config::SetupPaths()
{
    // Get the directory that the executable is in
    std::filesystem::path executableDirectory = std::filesystem::canonical(SDL_GetBasePath());

    Config::AssetsPath = executableDirectory / "assets";
    Config::TexturesPath = Config::AssetsPath / "textures";
    Config::PrefabsPath = Config::AssetsPath / "data/prefabs.json";
    Config::LevelsPath = Config::AssetsPath / "data/levels";
}
