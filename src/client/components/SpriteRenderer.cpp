#include "client/components/SpriteRenderer.hpp"
#include <iostream>
#include "common/core/GameObject.hpp"
#include "common/core/Config.hpp"
#include "common/core/JSONExtensions.hpp"
#include "common/core/GlmUtils.hpp"
#include "common/core/SdlUtils.hpp"
//
//SpriteRenderer::SpriteRenderer()
//{
////    m_Transform.translation = {0.0f, 0.0f, 0.0f};
////    m_Transform.rotation = {0.0f, 0.0f, 0.0f, 1.0f};
////    m_Transform.scale = {1.0f, 1.0f, 1.0f};
//}

SpriteRenderer::~SpriteRenderer()
{
    //dtor
}

void SpriteRenderer::ApplyDefaults(const nlohmann::json& defaultsJson)
{
    // Apply default transform values (position ("translation"), rotation, scale)
    nlohmann::json transformJson = JsonUtils::GetFromJson<nlohmann::json>(defaultsJson, "Transform");

    std::vector<float> position = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Position");
    m_Transform.Position = GlmUtils::Vec3FromStdVector(position);

    std::vector<float> rotation = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Rotation");
    m_Transform.Rotation = GlmUtils::QuatFromStdVector(rotation);

    std::vector<float> scale = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Scale");
    m_Transform.Scale = GlmUtils::Vec3FromStdVector(scale);

    // Set texture if provided (not necessary)
    if (defaultsJson.contains("Texture")){
        std::string textureName = JsonUtils::GetFromJson<std::string>(defaultsJson, "Texture");
        SetTexture(textureName);
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
            m_Transform.Position = GlmUtils::Vec3FromStdVector(position);
        }
        if (transformJson.contains("Rotation")) {
            std::vector<float> rotation = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Rotation");
            m_Transform.Rotation = GlmUtils::QuatFromStdVector(rotation);
        }
        if (transformJson.contains("Scale")) {
            std::vector<float> scale = JsonUtils::GetFromJson<std::vector<float>>(transformJson, "Scale");
            m_Transform.Scale = GlmUtils::Vec3FromStdVector(scale);
        }
    }
    // Texture
    if (overridesJson.contains("Texture"))
    {
        std::string textureName = JsonUtils::GetFromJson<std::string>(overridesJson, "Texture");
        SetTexture(Config::TexturesPath.string() + "/" + textureName);
    }
}


void SpriteRenderer::Update(double dt)
{

}

void SpriteRenderer::Draw()
{
// TODO: Draw based on owning GameObject's Transform
    if (!m_Texture) {
        std::cout << "Trying to render sprite with no texture." << std::endl;
        return;
    }
//    SDL_FRect destinationRect;
//    glm::vec2 globalPosition = {m_Transform.Position.x + m_Owner->GetTransform().Position.x,
//            m_Transform.Position.y + m_Owner->GetTransform().Position.y};
//    // Draw it in the center
//    destinationRect.x = globalPosition.x - 0.5f * m_Width;
//    destinationRect.y = globalPosition.y - 0.5f * m_Height;
//    destinationRect.w = m_Width * m_Transform.Scale.x * m_Owner->GetTransform().Scale.x;
//    destinationRect.h = m_Width * m_Transform.Scale.y * m_Owner->GetTransform().Scale.y;
//    SDL_FPoint localCenter = {0.5f * m_Width, 0.5f * m_Height};
//    float angle = 30.0f; // TODO: CONVERT TRANSLATION.ROTATION TO THIS ANGLE
//    SDL_RenderTextureRotated(m_Renderer, m_Texture.get(), NULL, &destinationRect, angle, &localCenter, SDL_FLIP_NONE);
    Transform ownerTransform = m_Owner->GetTransform();
    glm::vec3 globalCenter = m_Transform.Position + ownerTransform.Position;
    // rotate {1.0f, 0.0f, 0.0f} by m_Owner's Rotation followed by m_Transform.Rotation
    glm::vec3 rotatedRightDir = m_Transform.Rotation * ownerTransform.Rotation * glm::vec3(1.0f, 0.0f, 0.0f);
    // rotate {0.0f, 1.0f, 0.0f} by m_Owner's Rotation followed by m_Transform.Rotation
    glm::vec3 rotatedDownDir = m_Transform.Rotation * ownerTransform.Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 originVec3 = globalCenter - 0.5f * m_Width * rotatedRightDir;
    glm::vec3 rightVec3 = globalCenter + 0.5f * m_Width * rotatedRightDir;
    glm::vec3 downVec3 = globalCenter - 0.5f * m_Width * rotatedRightDir
                            + 0.5f * m_Height * rotatedDownDir;
    SDL_FPoint origin = SdlUtils::FPointFromGlmVec3(originVec3);
    SDL_FPoint right = SdlUtils::FPointFromGlmVec3(rightVec3);
    SDL_FPoint down = SdlUtils::FPointFromGlmVec3(downVec3);
    SDL_RenderTextureAffine(m_Renderer, m_Texture.get(), NULL, &origin, &right, &down);
}

void SpriteRenderer::SetTexture(const std::string& fileName)
{
    std::string fullPath = (Config::TexturesPath / fileName).string();
    SDL_Surface* surface = SDL_LoadPNG(fullPath.c_str());
    if (!surface) {
        std::cout << "ERROR: failed to create surface from '" << fullPath << "'." << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    if (!texture) {
        std::cout << "ERROR: failde to create texture from surface (of '" << fullPath << "')." << std::endl;
        return;
    }
    m_Texture.reset(texture);
    m_Width = surface->w;
    m_Height = surface->h;

    SDL_DestroySurface(surface);
}

