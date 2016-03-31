#version 330

in vec3 normal_vector;
in vec3 light_vector;
in vec3 halfway_vector;
in vec3 texture_coord;
uniform samplerCube cubemap;
out vec4 fragColor;

void main (void) {
	vec3 normal1         = normalize(normal_vector);
	vec3 light_vector1   = normalize(light_vector);
	vec3 halfway_vector1 = normalize(halfway_vector);

	vec4 c = vec4(1,1,1,1);//texture(cubemap, texture_coord);

	vec4 emissive_color = vec4(0.0, 1.0, 0.0, 1.0);
	vec4 ambient_color  = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 diffuse_color  = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 specular_color = vec4(0.0, 0.0, 1.0, 1.0);

	float emissive_contribution = 0.02;
	float ambient_contribution  = 0.20;
	float diffuse_contribution  = 0.40;
	float specular_contribution = 0.38;

	float d = dot(normal1, light_vector1);
	bool facing = d > 0.0;

	fragColor = emissive_color * emissive_contribution +
		    ambient_color  * ambient_contribution  * c +
		    diffuse_color  * diffuse_contribution  * c * max(d, 0) +
                    (facing ?
			specular_color * specular_contribution * c * pow(dot(normal1, halfway_vector1), 80.0) :
			vec4(0.0, 0.0, 0.0, 0.0));
	fragColor.a = 1.0;
}