#pragma once

#include <iostream>
// #include <GL/gl3w.h> for future
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
	GLfloat	x = 0.0;
	GLfloat	y = 0.0;
	GLfloat	z = 0.0;
	GLfloat	w = 1.0;
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
	vertex_buffer(int **map, int width, int height);
	GLfloat*	vertex_list;
	size_t		vertex_count;
private:
	void		form_triangles(GLfloat midpoint, int i, int j, int start, int** map);
	void		form_single_triangle(point& one, point& two, point& three, GLfloat* where);
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
	vertex_buffer	buffer;
	GLuint			shader_program;
	GLuint			VBO;
	GLuint			VAO;
	// void			framebuffer_size_callback(GLFWwindow* window, int width, int height);
/*private:
	SDL_Surface*	default_screen;
	SDL_Renderer*	renderer;
	SDL_Texture*	texture;
	void			render_texture(int* ret);
	camera			cam;
	vertex_buffer	buf;*/
};
