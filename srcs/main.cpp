#include "terrain.hpp"

OPENGL_stuff*	g_opengl_stuff = nullptr; // for callbacks

void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	(void)scancode;
	(void)mods;
	(void)window;

	static float last_time = glfwGetTime();

	float current_time = glfwGetTime();
	float delta = current_time - last_time;
	(void)delta;
	GLfloat cam_speed = 0.05f;
	if (g_opengl_stuff == nullptr)
		return ;
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_W)
			g_opengl_stuff->camera.position += cam_speed * g_opengl_stuff->camera.direction;
		if (key == GLFW_KEY_S)
			g_opengl_stuff->camera.position -= cam_speed * g_opengl_stuff->camera.direction;
		if (key == GLFW_KEY_A)
			g_opengl_stuff->camera.position -= cam_speed * g_opengl_stuff->camera.right_dir;
		if (key == GLFW_KEY_D)
			g_opengl_stuff->camera.position += cam_speed * g_opengl_stuff->camera.right_dir;
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	g_opengl_stuff->camera.compute_camera_matrix();
}

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
		g_opengl_stuff = &stuff;
		stuff.run();
	}
	catch (std::invalid_argument& exc) {
		std::cout << exc.what() << std::endl;
	}
	return (0);
}
