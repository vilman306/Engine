#pragma once

#include <vector>
#include <type_traits>
#include <cassert>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace GlmUtils
{

template <typename T>
glm::vec2 Vec2FromStdVector(const std::vector<T>& p_Vector)
{
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic.");
    if (p_Vector.size() < 2)
        throw std::runtime_error("ERROR: Argument p_Vector has too few elements (minimum is 2).");
    return {static_cast<float>(p_Vector[0]),
            static_cast<float>(p_Vector[1])};
}

template <typename T>
glm::vec3 Vec3FromStdVector(const std::vector<T>& p_Vector)
{
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic.");
    if (p_Vector.size() < 3)
        throw std::runtime_error("ERROR: Argument p_Vector has too few elements (minimum is 3).");
    return {static_cast<float>(p_Vector[0]),
            static_cast<float>(p_Vector[1]),
            static_cast<float>(p_Vector[2])};
}

template <typename T>
glm::quat QuatFromStdVector(const std::vector<T>& p_Vector)
{
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic.");
    if (p_Vector.size() < 4)
        throw std::runtime_error("ERROR: Argument p_Vector has too few elements (minimum is 4).");
    return {static_cast<float>(p_Vector[0]),
            static_cast<float>(p_Vector[1]),
            static_cast<float>(p_Vector[2]),
            static_cast<float>(p_Vector[3])};
}

}

