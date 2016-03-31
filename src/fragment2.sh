#version 330

in vec3 normal_vector;
in vec3 light_vector;
in vec3 halfway_vector;
in vec2 texture_coord;
uniform sampler2D texture_sample;
uniform sampler2D normal_sample;
uniform bool flag;
out vec4 fragColor;

void main (void) {
	vec3 normal1         = normalize(normal_vector);
	vec3 light_vector1   = normalize(light_vector);
	vec3 halfway_vector1 = normalize(halfway_vector);

	vec4 c = texture(texture_sample, texture_coord);
	vec3 n = normalize((texture(normal_sample, texture_coord).xyz-0.5)*2.0);
	normal1 = flag ? normalize(n.xyz+normal1) : normal1;

	vec4 emissive_color = vec4(0.0, 1.0, 0.0, 1.0);		// green
	vec4 ambient_color  = vec4(1.0, 1.0, 1.0, 1.0);		// white
	vec4 diffuse_color  = vec4(1.0, 1.0, 1.0, 1.0);		// white
	vec4 specular_color = vec4(1.0, 1.0, 1.0, 1.0);		// white

	float emissive_contribution = 0.01;
	float ambient_contribution  = 0.09;
	float diffuse_contribution  = 0.4;
	float specular_contribution = 0.9;

	float d = dot(normal1, light_vector1);
	bool facing = d > 0.0;

	fragColor = emissive_color * emissive_contribution +
		    ambient_color  * ambient_contribution  * c +
		    diffuse_color  * diffuse_contribution  * c * max(d, 0) +
                    (facing ?
			specular_color * specular_contribution * c * pow(max(0,dot(normal1, halfway_vector1)), 200.0) :
			vec4(0.0, 0.0, 0.0, 0.0));
	fragColor.a = 1.0;
}