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

#define ITER 1000

vec3 pal( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.28318*(c*t+d) );
}

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
	while (i < ITER && tmp.x + tmp.y < 64)
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
    utils = i - log2(log2(sqrt(tmp.x + tmp.y))) + 4.0;
		// utils = i - log(log(sqrt(tmp.x + tmp.y))) / log(2.0f);
    else
        utils = 0.0f;
    return (utils / ITER);
}

float de(vec3 pos){
    vec3 tpos=pos;
    tpos.xz=abs(.5-mod(tpos.xz,1.));
    vec4 p=vec4(tpos,1.);
    float y=max(0.,.35-abs(pos.y-3.35))/.35;
    for (int i=0; i<7; i++) {
      p.xyz = abs(p.xyz)-vec3(-0.02,1.98,-0.02);
      p=p*(2.0+0.*y)/clamp(dot(p.xyz,p.xyz),.4,1.)-vec4(0.5,1.,0.4,0.);
      p.xz*=mat2(-0.416,-0.91,0.91,-0.416);
    }
    return (length(max(abs(p.xyz)-vec3(0.1,5.0,0.1),vec3(0.0)))-0.05)/p.w;
  }

#define AA 4

void main()
{
  float l= 0;
   vec3 col = vec3(0.0);
    for( int m=0; m<AA; m++ )
    for( int n=0; n<AA; n++ )
    {
        vec2 p = vec2(ourPosition.x * ratio * zoom + x_pos, ourPosition.y * zoom + y_pos)+zoom * (vec2(float(m),float(n))/float(AA) / resolution.x);
        l = mandelbrot2(p.xy);
        l = clamp( pow(4.0*l,0.3), 0.0, 1.0 );
        col += pal( l + sin(time / 100), vec3(0.52,0.52,0.82),vec3(0.5,0.3,0.2),vec3(0.5,0.5,0.5),vec3(0.5,0.5,0.5) );
    } 
    col /= float(AA*AA);

  //  col += l*0.05 * zoom + vec3(0.0,0.6,1.0) * sin(time) + sin(time + 1.5) * vec3(0.7, 0.1, 0.0);
  // //  col = pal( l + sin(time / 100), vec3(0.42,0.42,0.42),vec3(0.5,0.5,0.5),vec3(.0,.6,1.0),vec3(0.0,0.33,0.67) );
  //  col = pal( l + sin(time / 100), vec3(0.52,0.52,0.82),vec3(0.5,0.3,0.2),vec3(0.5,0.5,0.5),vec3(0.5,0.5,0.5) );
   FragColor = vec4( col, 1.0 );
    if (l == 0.0f)
       FragColor = vec4 (0.0);
}