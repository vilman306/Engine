#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "common/core/Component.hpp"
#include "common/components/Transform.hpp"
#include "common/core/SceneComponent.hpp"

struct TextureDeleter
{
    void operator()(SDL_Texture* texture){
        SDL_DestroyTexture(texture);
    }
};

class SpriteRenderer : public SceneComponent
{
public:
    SpriteRenderer(SDL_Renderer* renderer) : SceneComponent(renderer) // forward renderer to SceneComponent
    {};
    virtual ~SpriteRenderer();

    virtual void ApplyDefaults(const nlohmann::json& defaultsJson) override;

    virtual void ApplyOverrides(const nlohmann::json& overridesJson) override;

    virtual void Update(double dt) override;

    virtual void Draw() override;

    SDL_Texture* GetTexture() { return m_Texture.get(); }

    void SetTexture(const std::string& fileName); // Loads image (png) to GPU




private:
    Transform m_Transform;
    std::unique_ptr<SDL_Texture, TextureDeleter> m_Texture;
    int m_Width = 0;
    int m_Height = 0;
};

#endif // SPRITERENDERER_HPP
