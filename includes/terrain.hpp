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

class camera_class
{
public:
	glm::vec3	direction;
	glm::vec3	upper_dir;
	glm::vec3	right_dir;
	glm::vec3	position;
	glm::mat4x4	cam_matrix;
	glm::mat4x4	projection;
	camera_class(int right, int up);
	void	compute_camera_matrix();
private:
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
	GLuint			create_shader_program(std::string vertex_shader_src, std::string fragment_shader_src);
private:
	heightmap		map;
	GLFWwindow*		window = NULL;
	GLFWwindow*		create_window();
	vertex_buffer	buffer;
	GLuint			shader_program;
	GLuint			water_program;
	GLuint			VBO;
	GLuint			VAO;
	GLuint			WATER_VBO;
	GLuint			WATER_VAO;
	// void			framebuffer_size_callback(GLFWwindow* window, int width, int height);
/*private:
	SDL_Surface*	default_screen;
	SDL_Renderer*	renderer;
	SDL_Texture*	texture;
	void			render_texture(int* ret);
	camera			cam;
	vertex_buffer	buf;*/
public:
	camera_class	camera;
	GLfloat			water_level;
};

void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
