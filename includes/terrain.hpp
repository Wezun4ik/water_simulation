#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#undef main
#include <exception>

const int width = 800;
const int height = 800;
const double pov = 3.1415 / 3.0;

struct	point
{
	float	x;
	float	y;
	float	z;
}

class camera
{
	point	one;
	point	two;
	point	three;
}


struct vertex
{
	point	one;
	point	two;
	point	three;
}

class heightmap
{
public:
	heightmap(const std::string& map_file);
	update_heightmap();
private:
	int**		data;
	size_t		width;
	size_t		heigth;
}

class vertex_buffer
{
public:
	vertex_buffer(const heightmap& map);
private:
	vertex*		vertex_list;
	size_t		vertex_count;
}

class SDL_stuff
{
public:
			SDL_stuff();
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
	vertex_buffer	buf;
};