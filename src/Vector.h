#ifndef VECTOR_H
#define VECTOR_H

/**
 * @brief A 2d-vector of type T.
 */
template <typename T>
struct v2 {
    T x, y;
};

/**
 * @brief A 3d-vector of type T.
 */
template <typename T>
struct v3 {
    T x, y, z;
};

/**
 * @brief A 4d-vector of type T.
 */
template <typename T>
struct v4 {
    T x, y, z, w;
};

/**
 * @brief A 2d-vector of type float.
 */
typedef v2<float> vec2;

/**
 * @brief A 2d-vector of type int.
 */
typedef v2<int> point;

/**
 * @brief A 3d-vector of type float.
 */
typedef v3<float> vec3;

/**
 * @brief A 4d-vector of type float.
 */
typedef v4<float> vec4;

#endif
