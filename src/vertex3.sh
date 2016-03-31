#version 330

in vec3 vertex;
in vec3 normal;
in vec3 k;
in float x;
in float y;
uniform float length_x;
uniform float length_y;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float time;
uniform sampler2D sample_real;
uniform sampler2D sample_imag;
uniform vec3 light_position;

out vec3 light_vector;
out vec3 normal_vector;
out vec3 halfway_vector;


float omega(float k) {
	return sqrt(k*9.81);
}

vec2 htilde(float Kx, float Ky, float kx, float ky, int dimx, int dimy, float time) {
	vec2 h0_tildeK = vec2(
				 texture(sample_real, vec2(kx/dimx,ky/dimy)).r,
				 texture(sample_imag, vec2(kx/dimx,ky/dimy)).r
	);
	vec2 h0_tildeKconj = vec2(
				 texture(sample_real, vec2((dimx-kx)/dimx,(dimy-ky)/dimy)).r
				-texture(sample_imag, vec2((dimx-kx)/dimx,(dimy-ky)/dimy)).r
	);
	float wK = omega(sqrt(Kx*Kx+Ky*Ky));
	float w0 = 3.14159265359*2.0/20.0;
	wK = floor(wK/w0)*w0;
	float cos_ = cos(wK*time);
	float sin_ = sin(wK*time);
	return vec2(h0_tildeK.x*cos_-h0_tildeK.y*sin_+
		    h0_tildeKconj.x*cos_-h0_tildeKconj.y*-sin_,

		    h0_tildeK.x*sin_+h0_tildeK.y*cos_+
		    h0_tildeKconj.x*-sin_+h0_tildeKconj.y*cos_
	);
}


void main() {
	vec3 v;
	v = vertex;

	int dimx = 64; int dimz = 64; float M_PI = 3.14159265359;
	//float length_x = 128;
	//float length_y = 128;

	float h = 0.0;
	vec2 D = vec2(0,0);
	vec2 Grad = vec2(0,0);
	float kx, ky, cos_, sin_;
	for (int j0 = 0, n = -dimz/2; j0 <= dimz; j0++, n++) {
		ky = M_PI*2.0*n/length_y;
		for (int i0 = 0, m = -dimx/2; i0 <= dimx; i0++, m++) {
			kx = M_PI*2.0*m/length_x;

			vec2 htilde_ = htilde(kx, ky, i0, j0, dimx, dimz, time);

			cos_ = cos(kx*v.x+ky*v.z);
			sin_ = sin(kx*v.x+ky*v.z);
			vec2 temp = vec2(
					htilde_.x*cos_-htilde_.y*sin_,
					htilde_.x*sin_+htilde_.y*cos_
				);
			h += temp.x;

			float sqroot = sqrt(m*m+n*n);
			if (sqroot == 0) sqroot = 1;
			D.x += temp.y*m/sqroot;
			D.y += temp.y*n/sqroot;

			Grad.x += temp.y*-m;
			Grad.y += temp.y*-n;
		}
	}

	float lambda = -2;
	v.x += lambda*D.x; v.z += lambda*D.y;
	v.y = h;

	normal_vector = vec3(0,1,0) - vec3(Grad.x,0,Grad.y);

//	if (length(normal_vector) < 0.001) normal_vector = vec3(0,1,0);

	gl_Position = Projection * View * Model * vec4(v, 1.0);

	v = (View * Model * vec4(v, 1.0)).xyz;
	light_vector = normalize((View * vec4(light_position, 1.0)).xyz - v.xyz);
	normal_vector = (inverse(transpose(View * Model)) * vec4(normal_vector, 0.0)).xyz;
        halfway_vector = light_vector + normalize(-v.xyz);

}