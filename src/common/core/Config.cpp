#include "common/core/Config.hpp"

std::filesystem::path Config::AssetsPath;
std::filesystem::path Config::TexturesPath;
std::filesystem::path Config::PrefabsPath;
std::filesystem::path Config::LevelsPath;


void Config::SetupPaths()
{
    // Get the directory that the executable is in
    std::filesystem::path executableDirectory;
    #ifdef __linux__
    executableDirectory = std::filesystem::canonical("/proc/self/exe").parent_path();
    #endif
    #ifdef _WIN32

    #endif
    // etc.

    // Set up assets path etc.
    Config::AssetsPath = executableDirectory / "assets";
    Config::TexturesPath = Config::AssetsPath / "textures";
    Config::PrefabsPath = Config::AssetsPath / "data/prefabs.json";
    Config::LevelsPath = Config::AssetsPath / "data/levels";
}
