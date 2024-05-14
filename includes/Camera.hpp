/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-14 14:06:38                                       *
*******************************************************************************/

#ifndef CAMERA_HPP
    #define CAMERA_HPP

    #include "ArcticFeather.hpp"

    class Camera
    {
        public:
            Matrix4 v;
            Matrix4 p;
            Camera(int width, int height,vec3 position)
            {
                this->width = width;
                this->height = height;
                Position = position;
            }
            void Matrix(float fov, float near, float far, Shader& shader, const char* uniform)
            {
                Matrix4 view;
                // view.translate(Position[0], Position[1], Position[2]);
                // vec3 origin(0.,0.,0.);
                vec3 tmp(Position[0] - Orientation[0], Position[1] - Orientation[1], Position[2] - Orientation[2]);
                view = vec3::lookAt(Position, tmp, Up);
                fov = fov / 2;
                std::vector<float> camera = {   1 / ((this->width / this->height) * (float)tan(fov * (M_PI / 360))), 0, 0, 0,
                                                0, 1 / (float)tan(fov * (M_PI / 360)), 0, 0,
                                                0, 0, -(far + near) / (far - near),  -2 * (far * near) / (far - near),
                                                0, 0, -1, 0};
                Matrix4 projection(camera);
                v = view;
                p = projection;
                shader.setMat("view", view.getData().data());
                shader.setMat("projection", projection.getData().data());
                (void)uniform;
            }
            
            void Inputs(GLFWwindow* window)
            {
                if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                {
                    speed = speed * 3;
                }
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    Position -= Orientation * speed;
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    Position += vec3::normalize(vec3::cross(Orientation, Up)) * speed * 0.3;
                }
                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    Position += Orientation * speed;
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    Position += -vec3::normalize(vec3::cross(Orientation, Up)) * speed * 0.3;
                }
                if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                {
                    Position += Up * speed;
                }
                if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                {
                    Position -= Up * speed;
                }
                if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
                {
                    speed *= 0.95;
                }
                if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
                {
                    speed *= 1.05;
                }
                if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                {
                    speed = speed / 3;
                }
                if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
                {
                    // Hides mouse cursor
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

                    // Prevents camera from jumping on the first click
                    if (firstClick)
                    {
                        glfwSetCursorPos(window, (width / 2), (height / 2));
                        firstClick = false;
                    }

                    // Stores the coordinates of the cursor
                    double mouseX;
                    double mouseY;
                    // Fetches the coordinates of the cursor
                    glfwGetCursorPos(window, &mouseX, &mouseY);

                    // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
                    // and then "transforms" them into degrees 
                    float rotX = -sensitivity * (float)(mouseY - (height / 2)) / height;
                    float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

                    // Calculates upcoming vertical change in the Orientation
                    vec3 newOrientation = vec3::rotate(Orientation, vec3::radians(-rotX), vec3::normalize(vec3::cross(Orientation, Up)));

                    // Decides whether or not the next vertical Orientation is legal or not
                    if (vec3::angle(newOrientation, Up) > vec3::radians(10.0f) && vec3::angle(newOrientation, Up) < vec3::radians(350.0f))
		            {
                        Orientation = newOrientation;
                    }

                    // Rotates the Orientation left and right
                    Orientation = vec3::rotate(Orientation, vec3::radians(-rotY), Up);

                    // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
                    glfwSetCursorPos(window, (width / 2), (height / 2));
                }
                else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
                {
                    // Unhides cursor since camera is not looking around anymore
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    // Makes sure the next time the camera looks around it doesn't jump
                    firstClick = true;
                }
            }
        private:
            vec3 Position;
            vec3 Orientation = vec3(0.0f, 0.0f, -1.0f);
            vec3 Up = vec3(0.0f, 1.0f, 0.0f);

            bool firstClick = true;

            int width;
            int height;

            float speed = .3f;
            float sensitivity = 100.0f;

            



            
    };

#endif