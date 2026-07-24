#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>

namespace Math
{

    struct Transform
    {
        raylib::Vector3 translation; // TODO: change name to position
        raylib::Quaternion rotation;
        raylib::Vector3 scale;
    };

}

#endif // MATH_HPP_INCLUDED
