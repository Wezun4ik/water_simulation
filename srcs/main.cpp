#include "terrain.hpp"

void	ensure_arguments(int argc)
{
	if (argc != 2)
	{
		std::cout << "There should be one argument: path to the heightmap" << std::endl;
		exit (0);
	}
}

int		main(int argc, char** argv)
{

	ensure_arguments(argc);
	std::string		file(argv[1]);
	try {
		OPENGL_stuff		stuff(file);
		stuff.run();
	}
	catch (std::invalid_argument& exc) {
		std::cout << exc.what() << std::endl;
	}
	return (0);
}
