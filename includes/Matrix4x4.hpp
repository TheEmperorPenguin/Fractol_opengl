/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-11 12:06:24                                       *
*******************************************************************************/

#ifndef MATRIX4X4_HPP
    #define MATRIX4X4_HPP

        #include "ArcticFeather.hpp"
        class Matrix4 : public Matrix<float>
        {
            public:
                Matrix4() : Matrix<float>((unsigned int)4)
                {
                }
                Matrix4(std::vector<float> input) : Matrix<float>(input, (unsigned int)4, (unsigned int)4)
                {
                }
                void translate(float x, float y, float z)
                {
                    this->setValue(x, 3, 0);
                    this->setValue(y, 3, 1);
                    this->setValue(z, 3, 2);
                }
                void scale(float size)
                {
                    float x, y, z;
                    z = y = x = size;
                    (*this).setValue(x, 0, 0);
                    (*this).setValue(0.0f, 0, 1);
                    (*this).setValue(0.0f, 0, 2);
                    (*this).setValue(0.0f, 0, 3);

                    (*this).setValue(0.0f, 1, 0);
                    (*this).setValue(y, 1, 1);
                    (*this).setValue(0.0f, 1, 2);
                    (*this).setValue(0.0f, 1, 3);

                    (*this).setValue(0.0f, 2, 0);
                    (*this).setValue(0.0f, 2, 1);
                    (*this).setValue(z, 2, 2);
                    (*this).setValue(0.0f, 2, 3);

                    (*this).setValue(0.0f, 3, 0);
                    (*this).setValue(0.0f, 3, 1);
                    (*this).setValue(0.0f, 3, 2);
                    (*this).setValue(1.0f, 3, 3);
                }
                void scale(float x, float y, float z)
                {
                    (*this).setValue(x, 0, 0);
                    (*this).setValue(0.0f, 0, 1);
                    (*this).setValue(0.0f, 0, 2);
                    (*this).setValue(0.0f, 0, 3);

                    (*this).setValue(0.0f, 1, 0);
                    (*this).setValue(y, 1, 1);
                    (*this).setValue(0.0f, 1, 2);
                    (*this).setValue(0.0f, 1, 3);

                    (*this).setValue(0.0f, 2, 0);
                    (*this).setValue(0.0f, 2, 1);
                    (*this).setValue(z, 2, 2);
                    (*this).setValue(0.0f, 2, 3);

                    (*this).setValue(0.0f, 3, 0);
                    (*this).setValue(0.0f, 3, 1);
                    (*this).setValue(0.0f, 3, 2);
                    (*this).setValue(1.0f, 3, 3);
                }
                void rotate(float radians, float x, float y, float z)
                {
                    float c = std::cos(radians);
                    float s = std::sin(radians);
                    float mag = std::sqrt(x * x + y * y + z * z);
                    if (mag > 0.0f) {
                        x /= mag;
                        y /= mag;
                        z /= mag;
                    }
                    float t = 1.0f - c;

                    // Construct rotation matrix
                    (*this).setValue(x * x * t + c,0, 0);
                    (*this).setValue(y * x * t + z * s,0, 1);
                    (*this).setValue(z * x * t - y * s,0, 2);
                    (*this).setValue(0.0f,0, 3);
                    (*this).setValue(x * y * t - z * s,1, 0);
                    (*this).setValue(y * y * t + c,1, 1);
                    (*this).setValue(z * y * t + x * s,1, 2);
                    (*this).setValue(0.0f,1, 3);
                    (*this).setValue(x * z * t + y * s,2, 0);
                    (*this).setValue(y * z * t - x * s,2, 1);
                    (*this).setValue(z * z * t + c,2, 2);
                    (*this).setValue(0.0f,2, 3);
                    (*this).setValue(0.0f,3, 0);
                    (*this).setValue(0.0f,3, 1);
                    (*this).setValue(0.0f,3, 2);
                    (*this).setValue(1.0f,3, 3);
                }
        };


#endif