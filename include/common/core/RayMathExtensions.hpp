#ifndef RAYLIBEXTENSIONS_HPP_INCLUDED
#define RAYLIBEXTENSIONS_HPP_INCLUDED

#include <raymath.hpp>
#include <vector>
#include <type_traits>
#include <cassert>

namespace RayUtils
{

template <typename T>
raylib::Vector2 RaylibVector2FromStdVector(const std::vector<T>& p_Vector)
{
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic.");
    if (p_Vector.size() < 2)
        throw std::runtime_error("ERROR: Argument p_Vector has too few elements (minimum is 2).");
    return {static_cast<float>(p_Vector[0]),
            static_cast<float>(p_Vector[1])};
}

template <typename T>
raylib::Vector3 RaylibVector3FromStdVector(const std::vector<T>& p_Vector)
{
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic.");
    if (p_Vector.size() < 3)
        throw std::runtime_error("ERROR: Argument p_Vector has too few elements (minimum is 3).");
    return {static_cast<float>(p_Vector[0]),
            static_cast<float>(p_Vector[1]),
            static_cast<float>(p_Vector[2])};
}

template <typename T>
raylib::Quaternion RaylibQuaternionFromStdVector(const std::vector<T>& p_Vector)
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

#endif // RAYLIBEXTENSIONS_HPP_INCLUDED
