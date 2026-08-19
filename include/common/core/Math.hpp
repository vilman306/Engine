#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

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
