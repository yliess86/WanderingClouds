#version 330 core

// MODES
// 0 - Manual    Procedural Random Generator
// 1 - Texture2D Procedural Random Generator
// 2 - Texture3D Predefined Volume
#define MODE           2

// RAYMARCHING
#define MAX_STEPS      512
#define MAX_DIST       512
#define MIN_DIST       0.00001
#define EPSILON        0.00001
#define DT             0.005
#define DT_DENSITY_POW 4

// NOISE
#define LAYERS         6
#define AM             0.5
#define FM             2.0

// CLOUDS
#define DENSITY_POW    3
#define DENSITY_THR    0.3

// LIGHTING
#define SUN_DIR        vec3(-1.00, 0.00, -1.00)
#define LIGHT_COL_1    vec3( 1.00, 0.95,  0.80)
#define LIGHT_COL_2    vec3( 1.00, 0.60,  0.30)
#define SHADOW_COL_1   vec3( 0.25, 0.30,  0.35)
#define SHADOW_COL_2   vec3( 0.65, 0.65,  0.75)

in vec2 v_uv;

out vec4 output;

uniform float     u_time;
uniform vec2      u_resolution;
uniform sampler2D u_noise2D;
uniform sampler3D u_noise3D;
uniform vec3      u_pos;

// ==== NOISE
#if(MODE != 2)

float hash21(vec2 p) {
#if(MODE == 1)
	return texture(u_noise2D, p * 0.01).x;

#else
	float s = sin(dot(p, vec2(12.9898, 78.233)));
	return fract(s * 43758.5453);

#endif
}

vec2 grad(vec2 p, float t) {
	float r = hash21(p);
	float a = 6.283185 * r + 4.0 * t * r;
	return vec2(cos(a), sin(a));
}

float noise(vec3 p) {
	vec2 f = fract(p.xy);
	vec2 i = floor(p.xy);
	
	vec2 l = f * f * (3.0 - 2.0 * f);
	vec2 d = vec2(0.0, 1.0);

	float bl = dot(grad(i + d.xx, p.z), f - d.xx);
	float br = dot(grad(i + d.yx, p.z), f - d.yx);
	float b  = mix(bl, br, l.x);
	
	float tl = dot(grad(i + d.xy, p.z), f - d.xy);
	float tr = dot(grad(i + d.yy, p.z), f - d.yy);
	float t  = mix(tl, tr, l.x);

	return 0.5 + 0.5 * mix(b, t, l.y) / 0.7;
}
 
float fbm(vec3 p, int layers, float am, float fm) {
	float s = 0.0;
	float a = 1.0;
	float w = 4.0;
	float r = a;
	for(int i = 0; i < layers; i++) {
		s += a * noise(w * p);
		a *= am;
		w *= fm;
		r += a;
	}
	return s / r;
}

#endif

// ==== SCENE
float clouds(vec3 p) {
	float n = 0;

#if(MODE == 2)
	n = texture(u_noise3D, p).r;

#else
	n = fbm(p, LAYERS, AM, FM);
	n = 1 - (0.5 + 0.5 * sin(1.5 + 3.14 * n));

#endif

	return pow(n, DENSITY_POW);
}

float scene(vec3 p){ return clouds(p); }

// ==== RAYMARCHING
vec4 raymarch(vec3 ro, vec3 rd, vec3 bg) {
	float t = 0.0;
	vec4  sum = vec4(0.0);

	for(int i = 0; i < MAX_STEPS; i++) {
		vec3 pos = ro + rd * t;
		float density = scene(pos);

		if (density > DENSITY_THR) {
			// ==== DIFFUSE & LIGHTING
			float dif = clamp(density - scene(pos + 0.3 * SUN_DIR) / 0.3, 0.0, 1.0);
			vec3  lin = SHADOW_COL_2 * 1.1 + 0.8 * LIGHT_COL_2 * dif;
			vec4  col = vec4(mix(LIGHT_COL_1, SHADOW_COL_1, density), density);
			col.xyz  *= lin;

			// ==== FOG
			col.xyz   = mix(col.xyz, bg, 1.0 - exp2(-0.075 * t));

			// ==== COMPOSITION
			col.w     = min(col.w * 8.0 * 0.05, 1.0);
			col.xyz  *= col.w;

			sum += col * (1.0 - sum.w);
		}

		t += DT * (1.0 - pow(density, DT_DENSITY_POW));
		if (t > MAX_DIST || sum.a > 1 - EPSILON) break;
	}

	return clamp(sum, 0.0, 1.0);
}

// ==== RENDERING
vec4 render(vec3 ro, vec3 rd) {
	float sun = clamp(dot(SUN_DIR, rd), 0.0, 1.0);
	
	vec3 bg  =       vec3(0.76, 0.75, 0.86);
	     bg -= 0.6 * vec3(0.90, 0.75, 0.95) * rd.y;
		 bg += 0.2 * vec3(1.00, 0.60, 0.10) * pow(sun, 8.0);

	vec4 res  = raymarch(ro, rd, bg);
	vec3 col  = bg * (1.0 - res.w) + res.xyz;
		 col += 0.2 * vec3(1.0, 0.4, 0.2) * pow(sun, 3.0);
		 col  = smoothstep(0.15, 1.1, col);

	return vec4(col, 1.0);
}

// ==== CAMERA
mat3 camera(vec3 ro, vec3 ta, float cr) {
	vec3 cw = normalize(ta -ro);
	vec3 cp = vec3(sin(cr), cos(cr), 0.0);
	vec3 cu = normalize(cross(cw, cp));
	vec3 cv = normalize(cross(cu, cw));
	return mat3(cu, cv, cw);
}

// ==== OUTPUT
void main() {
	vec2 a  = u_resolution.yx / u_resolution.y;
	vec2 p  = (2.0 * v_uv - 1.0) / a;

	vec3 to = vec3(
		0.3 * sin(0.1 * u_time),
		0.1 * cos(0.3 * u_time),
		0.3 * u_time
	);
	
	vec3 ro = u_pos;
	vec3 ta = ro + vec3(0.0, 0.0,  0.6) + to;

	mat3 ca = camera(ro, ta, 0.0);
	vec3 rd = ca * normalize(vec3(p, 2.5));
	
	output = sqrt(render(ro, rd));
}
