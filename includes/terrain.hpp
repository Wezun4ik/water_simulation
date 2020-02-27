#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#undef main
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

const int width = 800;
const int height = 800;
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

class SDL_stuff
{
public:
			SDL_stuff(std::string heightmap_path);
			~SDL_stuff();
	char*	return_pixels();
	void	run();

private:
	SDL_Window*		window;
	SDL_Surface*	default_screen;
	SDL_Renderer*	renderer;
	SDL_Texture*	texture;
	void			render_texture(int* ret);
	camera			cam;
	heightmap		map;
	vertex_buffer	buf;
};