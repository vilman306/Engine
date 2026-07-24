#include "client/components/SpriteRenderer.hpp"
#include <iostream>
#include "common/core/GameObject.hpp"
#include "common/core/Config.hpp"
#include "common/core/JSONExtensions.hpp"
#include "common/core/RaylibExtensions.hpp"

SpriteRenderer::SpriteRenderer()
{
//    m_Transform.translation = {0.0f, 0.0f, 0.0f};
//    m_Transform.rotation = {0.0f, 0.0f, 0.0f, 1.0f};
//    m_Transform.scale = {1.0f, 1.0f, 1.0f};
}

SpriteRenderer::~SpriteRenderer()
{
    //dtor
}

void SpriteRenderer::SetTexture(const std::string& path)
{
    m_Texture.Load(path);
}

void SpriteRenderer::ApplyDefaults(const nlohmann::json& defaultsJson)
{
    // Apply default transform values (position ("translation"), rotation, scale)
    nlohmann::json transformJson = JsonUtils::GetFromJson<nlohmann::json>(defaultsJson, "Transform");

    std::vector<float> position = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Position");
    m_Transform.translation = RayUtils::RaylibVector3FromStdVector(position);

    std::vector<float> rotation = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Rotation");
    m_Transform.rotation = RayUtils::RaylibQuaternionFromStdVector(rotation);

    std::vector<float> scale = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Scale");
    m_Transform.scale = RayUtils::RaylibVector3FromStdVector(scale);

    // Set texture if provided (not necessary)
    if (defaultsJson.contains("Texture")){
        std::string textureName = JsonUtils::GetFromJson<std::string>(defaultsJson, "Texture");
        SetTexture(Config::TexturesPath.string() + "/" + textureName);
    }
}

void SpriteRenderer::ApplyOverrides(const nlohmann::json& overridesJson)
{
    // Transform (position, rotation, scale)
    if (overridesJson.contains("Transform"))
    {
        nlohmann::json transformJson = JsonUtils::GetFromJson<nlohmann::json>(overridesJson, "Transform");
        if (transformJson.contains("Position")) {
            std::vector<float> position = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Position");
            m_Transform.translation = RayUtils::RaylibVector3FromStdVector(position);
        }
        if (transformJson.contains("Rotation")) {
            std::vector<float> rotation = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Rotation");
            m_Transform.rotation = RayUtils::RaylibQuaternionFromStdVector(rotation);
        }
        if (transformJson.contains("Scale")) {
            std::vector<float> scale = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Scale");
            m_Transform.scale = RayUtils::RaylibVector3FromStdVector(scale);
        }
    }
    // Texture
    if (overridesJson.contains("Texture"))
    {
        std::string textureName = JsonUtils::GetFromJson<std::string>(overridesJson, "Texture");
        SetTexture(Config::TexturesPath.string() + "/" + textureName);
    }
}


void SpriteRenderer::Draw()
{
    raylib::Vector3 ownerTranslation = m_Owner->transform.translation;
    raylib::Vector3 translation3D = ownerTranslation + m_Transform.translation;
    raylib::Vector2 translation2D = {translation3D.x, translation3D.y};
    m_Texture.Draw(translation2D);
}

void SpriteRenderer::Update(double dt)
{

}
