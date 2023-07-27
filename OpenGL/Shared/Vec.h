#pragma once

namespace shrd
{
    
    template<typename T>
    struct Vec3
    {
        T x, y, z;
    };

    template<typename T>
    struct Vec2
    {
        T x, y;
    };

}

typedef shrd::Vec3<float> vec3f;
typedef shrd::Vec3<int> vec3i;
typedef shrd::Vec3<unsigned int> vec3ui;
