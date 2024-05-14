/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-14 14:28:15                                       *
*******************************************************************************/

#version 330 core
 
out vec4 FragColor;
in vec3 ourPosition;
uniform float time;
uniform vec2  resolution;

float ratio = resolution.x / resolution.y;



void main()
{
   FragColor = vec4(cos((ourPosition.x * ratio * sin(time / 30))), ourPosition.y, sin(ourPosition.z * cos(time / 20)), 1.0);
}