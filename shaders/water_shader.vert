#version 330 core

layout (location = 0) in vec3 position;

uniform float water_level;
uniform mat4 camera;
uniform mat4 projection;
out vec4 vertex_color;

#define DIVIDE 15.0

void main()
{
	// gl_Position = vec4(position.x / 120.0 - 0.8, position.y / 120.0 - 0.5, position.z / 100.0, 1.0);
	gl_Position = projection * camera * vec4(vec2(position.xy), position.z + water_level * 50.0 - 5.0, 1.0);
	vertex_color = vec4(0.0, 0.0, 1.0, water_level * 1.5);
	// if (position.z / DIVIDE <= water_level)
	// 	vertex_color = vec4(0.0, 0.0, clamp(0.1, position.z / DIVIDE * 2.0, 1.0), 1.0);
	// else if (position.z / DIVIDE < 0.70)
	// 	vertex_color = vec4(0.902, 0.298, 0.0196, 1.0) * vec4(position.z / DIVIDE / 0.7);
	// else
	// 	vertex_color = vec4(vec3(position.z / DIVIDE), 1.0);
}
