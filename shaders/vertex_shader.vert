#version 330 core

layout (location = 0) in vec3 position;

out vec4 vertex_color;

void main()
{
	gl_Position = vec4(position.x / 120.0 - 0.8, position.y / 120.0 - 0.5, position.z / 100.0, 1.0);
	if (position.z / 15.0 < 0.37)
		vertex_color = vec4(0.0, 0.0, max(position.z / 15.0 * 2.0, 0.1), 1.0);
	else if (position.z / 15.0 < 0.70)
		vertex_color = vec4(0.0, position.z / 0.7 / 15.0, 0.0, 1.0);
	else
		vertex_color = vec4(vec3(position.z / 15.0), 1.0);
}
