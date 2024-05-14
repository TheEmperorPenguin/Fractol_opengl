/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-12 14:37:26                                       *
*******************************************************************************/

#ifndef VEC3_HPP
    #define VEC3_HPP
        #include "ArcticFeather.hpp"
        #include "Matrix4x4.hpp"
        class Matrix4;
        class vec3 : public Matrix<float>
        {
            public:
                vec3() : Matrix<float>(3, 1)
                {
                }
                vec3(std::vector<float> input) : Matrix<float>(input, (unsigned int)3, (unsigned int)1)
                {
                }
                vec3(float x, float y, float z) : Matrix<float>({x, y, z}, (unsigned int)3, (unsigned int)1)
                {
                }
                vec3  &operator -()
                {
                    this->setValue(-this->getValue(0, 0), 0, 0);
                    this->setValue(-this->getValue(1, 0), 1, 0);
                    this->setValue(-this->getValue(2, 0), 2, 0);
                    return (*this);
                }
                float  operator [](int index) const
                {
                    return (this->getValue(index, 0));
                }
                static vec3 cross(vec3 a, vec3 b)
                {
                    float x =  a[1]*b[2]-a[2]*b[1];
                    float y =  a[2]*b[0]-a[0]*b[2];
                    float z =  a[0]*b[1]-a[1]*b[0];
                    vec3 result(x,y,z);
                    return (result);
                }
                static vec3 normalize(vec3 v)
                {
                    float length_of_v = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
                    return vec3(v[0] / length_of_v, v[1] / length_of_v, v[2] / length_of_v);
                }
                static float radians(float angle)
                {
                    return (angle * (M_PI / 360));
                }
                static float mag(vec3 v)
                {
                    return sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
                }
                static float dot(vec3 a, vec3 b)
                {
                    return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
                }
                static float angle(vec3 & a, vec3 & b)
                {
                    return acos(dot(a,b)/(mag(a)*mag(b)));
                }
                static Matrix4 lookAt(vec3 & eye, vec3 & center,vec3 & up)
                {
                    vec3 tmp(center[0] - eye[0], center[1] - eye[1], center[2] - eye[2]); 
                    vec3 f = vec3::normalize(tmp);
                    vec3 s = vec3::normalize(vec3::cross(f, up));
                    vec3 u = vec3::normalize(vec3::cross(s, f));

                    // Create the view matrix
                    std::vector<float> input = {s[0], s[1], s[2], -vec3::dot(s, eye),
                                                u[0], u[1], u[2], -vec3::dot(u, eye),
                                                -f[0], -f[1], -f[2], vec3::dot(f, eye),
                                                0, 0, 0, 1};
                    Matrix4 result(input);
                    return result;
                }
                static vec3 rotate(vec3 & v, float angle, vec3 axis)
                {
                    vec3 result;
                    Matrix4 rotationMatrix;
                    rotationMatrix.rotate(angle, axis[0], axis[1], axis[2]);
                    result.setValue(rotationMatrix.getValue(0,0) * v[0] + rotationMatrix.getValue(1,0) * v[1] + rotationMatrix.getValue(2,0) * v[2], 0, 0);
                    result.setValue(rotationMatrix.getValue(0,1) * v[0] + rotationMatrix.getValue(1,1) * v[1] + rotationMatrix.getValue(2,1) * v[2], 1, 0);
                    result.setValue(rotationMatrix.getValue(0,2) * v[0] + rotationMatrix.getValue(1,2) * v[1] + rotationMatrix.getValue(2,2) * v[2], 2, 0);
                    return (result);
                }
        };


#endif