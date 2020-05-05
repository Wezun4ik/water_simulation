#pragma once

#include <iostream>
// #include <GL/gl3w.h> for future
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

const int width = 1024;
const int height = 720;
const double pov = 3.1415 / 3.0;

struct	point
{
	float	x = 0.0;
	float	y = 0.0;
	float	z = 0.0;
	float	w = 1.0;
};

class camera
{
	point	one;
	point	two;
	point	three;
};

struct vertex
{
	point	one;
	point	two;
	point	three;
};

struct heightmap
{
	heightmap(const std::string& map_file_path);
	// update_heightmap();
	int**		data;
	size_t		width = 0;
	size_t		height = 0;
};

class vertex_buffer
{
public:
	// vertex_buffer(const heightmap& map);
private:
	vertex*		vertex_list;
	size_t		vertex_count;
};

class OPENGL_stuff
{
public:
	OPENGL_stuff(std::string heightmap_path);
	~OPENGL_stuff();
	void			run();
private:
	heightmap		map;
	GLFWwindow*		window = NULL;
	GLFWwindow*		create_window();
	// void			framebuffer_size_callback(GLFWwindow* window, int width, int height);
/*private:
	SDL_Surface*	default_screen;
	SDL_Renderer*	renderer;
	SDL_Texture*	texture;
	void			render_texture(int* ret);
	camera			cam;
	vertex_buffer	buf;*/
};
