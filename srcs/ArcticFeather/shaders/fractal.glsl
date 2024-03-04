/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-04 19:01:16                                       *
*******************************************************************************/

#version 330 core
 
out vec4 FragColor;
in vec3 ourPosition;
uniform float time;
uniform float x_pos;
uniform float y_pos;
uniform float zoom;
uniform vec2  resolution;
const float borderThickness = 0.01;
const vec4 borderColor = vec4(1.0, 1.0, 0.0, 1.0);
const vec4 fillColor = vec4(1.0, 0.0, 0.0, 1.0);
const float radius = 0.05;
float ratio = resolution.x / resolution.y;

vec3 pal( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.28318*(c*t+d) );
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

float mandelbulb(vec3 pos) {
	vec3 z = pos;
	float dr = 1.0;
	float r = 0.0;
  float power = 2 * 3.15 + 2 * cos(time / 10);
	for (int i = 0; i < 512 ; i++) {
		r = length(z);
		if (r>10.) break;
		
		// convert to polar coordinates
		float theta = acos(z.z/r);
		float phi = atan(z.y,z.x);
		dr =  pow( r, power-1.0)*power*dr + 1.0;
		
		// scale and rotate the point
		float zr = pow( r,power);
		theta = theta*power;
		phi = phi*power;
		
		// convert back to cartesian coordinates
		z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z+=pos;
	} 
	return 0.5*log(r)*r/dr;
}

float smin( float a, float b, float k )
{
    k *= 1.0;
    float res = exp2( -a/k ) + exp2( -b/k );
    return -k*log2( res );
}

float sdSphere(vec3 position, float radius)
{
  return length(position) - radius;
}

float sdBox(vec3 position, vec3 b)
{
  vec3 q = abs(position) - b;
  return length(max(q, 0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

float map(vec3 position) 
{
  // vec3 spherePos = vec3(0.,2.,0.);
  // vec3 boxPos = vec3(2.,2.,0.);
  float mandel = mandelbulb((position));
  // float de = de((position) * 0.1) * 10.;
  // float sphere = sdSphere(position - spherePos, 1.);
  // float box = sdBox(position - boxPos, vec3(.75));

  // float ground = position.y + 0.75;
  return mandel;
  // return min(mandel,min(ground, min(de, smin(sphere, box, .1))));
}

vec3 calculate_normal(in vec3 p)
{
	  float d = map(p);
    vec2 e = vec2(.001, 0);
    
    vec3 n = d - vec3(
        map(p-e.xyy),
        map(p-e.yxy),
        map(p-e.yyx));
    
    return normalize(n);
}


float softshadow( in vec3 ro, in vec3 rd, float mint, float maxt, float k )
{
    float res = 1.0;
    float t = mint;
    for( int i=0; i<256 && t<maxt; i++ )
    {
        float h = map(ro + rd*t);
        if( h<0.001 )
            return 0.0;
        res = min( res, k*h/t );
        t += h;
    }
    return res;
}

void main() {
    vec2 uv = (gl_FragCoord.xy * 2. - resolution.xy) / resolution.y;

    vec3 ray_origin = vec3(x_pos, 0, -3 + y_pos);
    vec3 ray_direction = normalize(vec3(uv * 1., 1));
    vec3 color = vec3(0 );
  vec3 normal = vec3(1.0);
    float travelled_distance = 0.;
    float diffuse_intensity = 1.;
    vec3 position = vec3(1.);
    for (int i = 0; i < 1024; i++) {
        position = ray_origin + ray_direction * travelled_distance;

        float dist = map(position);

        travelled_distance += dist;

        if (dist < .001)
        {
          // normal = calculate_normal(position) * 0.5 + 0.5;
          // vec3 light_position = vec3(2., 2.0, 5.0);
          // vec3 direction_to_light = normalize(position - light_position);
          // diffuse_intensity = max(0.0, dot(normal, direction_to_light));
          // normal = normal * pal( distance, vec3(0.8,0.5,0.4),vec3(0.2,0.4,0.2),vec3(2.0,1.0,1.0),vec3(0.0,0.25,0.25) );
          // float shad = softshadow(position, direction_to_light, 0.01, 3, 2.);
          // diffuse_intensity = 0.5 * diffuse_intensity + 0.5 * shad;
          color = pal( exp(distance(position, vec3(0.0))) + sin(time / 100) , vec3(0.42,0.42,0.42),vec3(0.5,0.5,0.5),vec3(.0,.6,1.0),vec3(0.0,0.33,0.67) );
          break;
        }
        if (travelled_distance > 100.)
        {
          color = vec3(0.,0.,0.);
          break;
        }
    }
    
    // color = vec3(normal) * diffuse_intensity * vec3(0.5,0.5,0.7);           // color based on distance
    FragColor = vec4(color, 1);
}