/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-02-29 14:37:09                                       *
*******************************************************************************/

#version 330 core
 
out vec4 FragColor;
in vec3 ourPosition;
uniform float time;
uniform float x_pos;
uniform float y_pos;
uniform float zoom;
uniform vec2  resolution;

float ratio = resolution.x / resolution.y;

#define ITER 8192

float mandelbrot2( in vec2 c )
{

    float c2 = dot(c, c);
    if( 256.0*c2*c2 - 96.0*c2 + 32.0*c.x - 3.0 < 0.0 ) return 0.0;
    if( 16.0*(c2+2.0*c.x+1.0) - 1.0 < 0.0 ) return 0.0;
    vec2	tmp;
	vec2	res;
	float	utils;
	int		i;

	utils = c.x;
	res.x = 0;
	res.y = 0;
	tmp.x = 0;
	tmp.y = 0;
	i = 0;
	while (i < ITER && tmp.x + tmp.y <  ITER)
	{
		utils = res.x;
		res.x = c.x + tmp.x - tmp.y ;
		res.y = c.y + (utils + utils) * res.y;
		tmp.x = res.x * res.x;
		tmp.y = res.y * res.y;
		i++;
	}
	utils = i;
	if (i != ITER)
		utils = i - log(log(sqrt(tmp.x + tmp.y))) / log(2.0f);
    else
        utils = 0.0f;
    return (utils);
}

void main()
{

   vec3 col = vec3(0.0);
   float l = mandelbrot2(vec2((ourPosition.x * ratio * zoom) + x_pos, ourPosition.y * zoom + y_pos));
   col += l*0.05 * zoom + vec3(0.0,0.6,1.0) * sin(time) + sin(time + 1.5) * vec3(0.7, 0.1, 0.0);
   FragColor = vec4( col, 1.0 );
   if (l == 0.0f)
      FragColor = vec4 (0.0);
}