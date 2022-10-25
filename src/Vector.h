#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
struct v2 {
    T x, y;
};

template <typename T>
struct v3 {
    T x, y, z;
};

template <typename T>
struct v4 {
    T x, y, z, w;
};

typedef v2<float> vec2;
typedef v2<int> point;

typedef v3<float> vec3;

typedef v4<float> vec4;

#endif
