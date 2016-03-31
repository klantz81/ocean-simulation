#version 330

in vec3 vertex;
in vec3 normal;
in vec3 texture;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform vec3 light_position;

out vec3 light_vector;
out vec3 normal_vector;
out vec3 halfway_vector;
out float fog_factor;
out vec2 tex_coord;

void main() {
	gl_Position = View * Model * vec4(vertex, 1.0);
	fog_factor = min(-gl_Position.z/500.0, 1.0);
	gl_Position = Projection * gl_Position;

	vec4 v = View * Model * vec4(vertex, 1.0);
	vec3 normal1 = normalize(normal);

	light_vector = normalize((View * vec4(light_position, 1.0)).xyz - v.xyz);
	normal_vector = (inverse(transpose(View * Model)) * vec4(normal1, 0.0)).xyz;
        halfway_vector = light_vector + normalize(-v.xyz);

	tex_coord = texture.xy;
}