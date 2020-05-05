#include "terrain.hpp"

GLFWwindow*		OPENGL_stuff::create_window() {
	auto		ret = glfwCreateWindow(width, height, "BRUH", NULL, NULL);
	if (ret == NULL)
		throw(std::runtime_error("Window not initialized"));
	return (ret);
}

void			framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	(void)window;
	glViewport(0, 0, width, height);
}

void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	(void)scancode;
	(void)mods;
	(void)window;

	static float last_time = glfwGetTime();

	float current_time = glfwGetTime();
	float delta = current_time - last_time;
	(void)delta;
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

OPENGL_stuff::OPENGL_stuff(std::string heightmap_path): map(heightmap_path) {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = create_window();
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		throw (std::runtime_error("GLEW not loaded"));

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_DEPTH);
}

OPENGL_stuff::~OPENGL_stuff() {
	// glfwDestroyWindow(window);
}

void			OPENGL_stuff::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
