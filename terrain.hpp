#ifndef TERRAIN_H
# define TERRAIN_H
# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>
# include <iostream>
# include <stdexcept>
# include <cstdlib>
# include <string.h>
# include <vector>
// # define PRINT
// # define NDEBUG

const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<const char*> validation_layers =
{"VK_LAYER_LUNARG_standard_validation"};

# ifdef NDEBUG
	const bool enable_validation_layers = false;
#  else
	const bool enable_validation_layers = true;
# endif
#endif
