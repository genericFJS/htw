#version 420 core  // 450, 330 core , compatibility
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 text_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_mat;

out vec3 vs_frag_pos;
out vec3 vs_normal;
out vec2 vs_text_coord;

void main() { 
	gl_Position = projection * view *  model  * vec4(position, 1.0f);
	vs_frag_pos = vec3(model * vec4(position, 1.0f));
	vs_text_coord = vec2(text_coord.x , text_coord.y);
	vs_normal = normal_mat * normal;
}