#version 460 core
layout(location = 0) in vec2 v_position;
layout(location = 1) in vec2 v_texture;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
out vec2 TexCoord;
void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(v_position, 0.0, 1.0);
	TexCoord = v_texture;
}