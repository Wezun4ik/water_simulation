#include "terrain.hpp"

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

char*	SDL_stuff::return_pixels()
{
	return(static_cast<char*>(default_screen->pixels));
}

void	SDL_stuff::run()
{
	int	happened = 1;
	int	quit = 0;
	while (!quit)
	{
		SDL_Event	event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				quit = 1;
				break;
			}
		}
		if (happened)
		{
			happened = 0;
			render_texture((int*)(this->return_pixels()));
		}
		SDL_UpdateTexture(texture, 0, this->return_pixels(), default_screen->w * sizeof(int));
		SDL_RenderCopy(renderer, texture, 0, 0);
		SDL_RenderPresent(renderer);
	}
}

void	SDL_stuff::render_texture(int *buf)
{
	for (int i = 0; i < width * height; ++i)
	{
		buf[i] = 0xFF0000;
	}
}

SDL_stuff::SDL_stuff(): par(5.0, 0.0, 0.0)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "could not initialize sdl2: " << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow(
		"Nice cock bro",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_SHOWN
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	default_screen = SDL_CreateRGBSurface(0, width, height, 32,
		0x00FF0000,
		0x0000FF00,
		0x000000FF,
		0xFF000000);
	if (default_screen == NULL)
		SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

SDL_stuff::~SDL_stuff()
{
	SDL_FreeSurface(default_screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int		main()
{
	SDL_stuff		stuff;
	stuff.run();
	return (0);
}