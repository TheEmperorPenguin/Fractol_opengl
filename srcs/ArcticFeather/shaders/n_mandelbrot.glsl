/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-04 17:30:29                                       *
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


#define cx_mul(a, b) vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x)
#define cx_div(a, b) vec2(((a.x*b.x+a.y*b.y)/(b.x*b.x+b.y*b.y)),((a.y*b.x-a.x*b.y)/(b.x*b.x+b.y*b.y)))

vec3 pal( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.28318*(c*t+d) );
}

vec2 squareImaginary(vec2 number){
	return vec2(
		pow(number.x,2)-pow(number.y,2),
		2*number.x*number.y
	);
}

vec2 GiveReflection(vec2 C) {
    
    vec2 Z = vec2(0.0); // initial value for iteration Z0
    vec2 dC = vec2(0.0); // derivative with respect to c 
    float reflection = 0; // inside 
    
    float h2 = 1.4; // height factor of the incoming light
    float angle = (time * 100) / 360.0; // incoming direction of light in turns 
    vec2 v = vec2(cos(2.0 * angle * 3.14159), sin(2.0 * angle * 3.14159));
    vec2 u;

    for (int i = 0; i < ITER; i++) {
        dC = 2.0 * cx_mul(dC, Z) + vec2(1.0);
        Z = squareImaginary(Z) + C;

        if (length(Z) > 10000.) { // exterior of M set
            u = cx_div(Z, dC);
            u = u / length(u);
            reflection = dot(u, v) + h2;
            reflection = reflection / (1.0 + h2);
            if (reflection < 0.0) reflection = 0.0;

            return vec2(reflection, (i - log2(log2(length(Z))) + 4.0) / (ITER));
        }
    }

    return vec2(reflection, 0);
}

#define AA 2

void main()
{
    vec2 l = vec2(0);
    vec3 col = vec3(0.0);
    #ifdef AA
        for( int m=0; m<AA; m++ )
        for( int n=0; n<AA; n++ )
        {
            vec2 p = vec2(ourPosition.x * ratio * zoom + x_pos, ourPosition.y * zoom + y_pos)+zoom * (vec2(float(m),float(n))/float(AA) / resolution.x);
            l = GiveReflection(p.xy);
            // col += l.x * pal(l.y * 50, vec3(0.42,0.42,0.42),vec3(0.5,0.5,0.5),vec3(.0,.6,1.0),vec3(0.0,0.33,0.67) );
            col+= l.x;
        } 
        col /= float(AA*AA);
        FragColor = vec4(col, 1.0 );
        if (l.y == 0.0f)
            FragColor = vec4 (0.,0,0.,0);
    #else
        vec2 p = vec2(ourPosition.x * ratio * zoom + x_pos, ourPosition.y * zoom + y_pos);
        l = GiveReflection(p.xy);
        FragColor = vec4(pal(l.y, vec3(0.42,0.42,0.42),vec3(0.5,0.5,0.5),vec3(.0,.6,1.0),vec3(0.0,0.33,0.67) ), 1.0);
        FragColor = vec4(FragColor.xyz * l.x, 1.0 );
        if (l.y == 0.0f)
            FragColor = vec4 (0.,0,0.5,0);
    #endif
}