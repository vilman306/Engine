#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "common/core/Component.hpp"
#include <raylib-cpp.hpp>
#include "common/core/SceneComponent.hpp"

class SpriteRenderer : public SceneComponent
{
public:
    SpriteRenderer();
    virtual ~SpriteRenderer();

    const raylib::Texture& GetTexture() // TODO
    {
        return m_Texture;
    }
    void SetTexture(const std::string& path);

    virtual void ApplyDefaults(const nlohmann::json& defaultsJson) override;

    virtual void ApplyOverrides(const nlohmann::json& overridesJson) override;

    virtual void Update(double dt) override;

    virtual void Draw() override;


private:
    Transform m_Transform;
    raylib::Texture m_Texture;
};

#endif // SPRITERENDERER_HPP
