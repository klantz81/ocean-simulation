#version 330

in vec3 vertex;
in vec3 normal;
in vec3 texcoord;
in vec3 _tangent;
in vec3 _bitangent;
in vec3 _normal;
uniform vec3 light_position;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
out vec3 light_vector;
out vec3 normal_vector;
out vec3 halfway_vector;
out vec2 texture_coord;


void main() {
	gl_Position = Projection * View * Model * vec4(vertex, 1.0);

	mat3 tbni = inverse(mat3(_tangent, _bitangent, _normal));

	vec4 v        = Model * vec4(vertex, 1.0);					// vertex in model space
	light_vector  = tbni * (inverse(Model) * vec4(light_position - v.xyz, 0)).xyz;	// light vector in tangent space

	v = View * Model * vec4(vertex, 1.0);						// vertex in eye space
	vec4 light_vector_eye  = normalize((View * vec4(light_position, 1.0)) - v);	// light vector in eye space
	vec4 viewer_vector_eye = normalize(-v);						// view vector in eye space

	halfway_vector = tbni * (inverse(View * Model) * vec4((light_vector_eye.xyz + viewer_vector_eye.xyz), 0.0)).xyz;
											// halfway vector in tangent space
	normal_vector = inverse(transpose(tbni)) * normal;

	texture_coord = texcoord.xy;
}