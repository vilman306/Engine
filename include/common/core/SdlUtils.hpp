#pragma once

#include <SDL3/SDL_rect.h>

namespace SdlUtils {

SDL_FPoint FPointFromGlmVec3(glm::vec3 vec3) {
    SDL_FPoint result;
    result.x = vec3.x;
    result.y = vec3.y;
    return result;
}

}
