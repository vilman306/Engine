#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <filesystem>

namespace Config
{
const float WindowWidth = 1920;
const float WindowHeight = 1080;
constexpr const char* WindowTitle = "Game Title";
void SetupPaths();

extern std::filesystem::path AssetsPath;
extern std::filesystem::path TexturesPath;
extern std::filesystem::path PrefabsPath;
extern std::filesystem::path LevelsPath;
}
#endif // CONFIG_H_INCLUDED
