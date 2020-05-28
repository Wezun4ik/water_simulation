#version 330 core

in vec4 vertex_color;

out vec4 color;

float znear = 0.1;
float zfar = 100.0;

float linearize(float depth)
{
	float z = depth * 2.0 - 1.0;
	return ((2.0 * znear * zfar) / (zfar + znear - z * (zfar - znear)));
}

void main()
{
	color = vertex_color;
	// float depth = linearize(gl_FragCoord.z) / zfar;
	// color = vec4(vec3(depth), 1.0);
}
