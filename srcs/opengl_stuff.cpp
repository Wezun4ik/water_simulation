#include "terrain.hpp"

// void			vertex_buffer::form_triangles(GLfloat midpoint, int i, int j, int start, int** map) {
// 	auto		upper_left_corner = (GLfloat)map[i][j];
// 	auto		upper_right_corner = (GLfloat)map[i][j + 1];
// 	auto		down_left_corner = (GLfloat)map[i + 1][j];
// 	auto		down_right_corner = (GLfloat)map[i + 1][j + 1];
// 	auto		upper_middle_point = (upper_left_corner + upper_right_corner) / 2.0f;
// 	auto		left_middle_point =

// }

void			vertex_buffer::form_single_triangle(point& one, point& two, point& three, GLfloat* where) {
	where[0] = one.x;
	where[1] = one.y;
	where[2] = one.z;
	where[3] = two.x;
	where[4] = two.y;
	where[5] = two.z;
	where[6] = three.x;
	where[7] = three.y;
	where[8] = three.z;
}

void			vertex_buffer::form_triangles(GLfloat midpoint, int i, int j, int start, int** map) {
	point		upper_left = {(GLfloat)j, midpoint - (GLfloat)i, (GLfloat)map[i][j]};
	point		upper_right = {(GLfloat)j + 1.0f, midpoint - (GLfloat)i, (GLfloat)map[i][j + 1]};
	point		down_left = {(GLfloat)j, midpoint - (GLfloat)i - 1.0f, (GLfloat)map[i + 1][j]};
	point		down_right = {(GLfloat)j + 1.0f, midpoint - (GLfloat)i - 1.0f, (GLfloat)map[i + 1][j + 1]};
	form_single_triangle(upper_left, down_left, upper_right, &(vertex_list[start]));
	form_single_triangle(upper_right, down_left, down_right, &(vertex_list[start + 9]));
}

vertex_buffer::vertex_buffer(int** map, int map_width, int map_height) {
	// vertex_count = (width - 1) * (height - 1) * 8; //FLOWER METHOD
	vertex_count = (map_width - 1) * (map_height - 1) * 2;
	vertex_list = new GLfloat[vertex_count * 9];
	int			count = 0;
	for (int i = 0; i + 1 < map_height; ++i) {
		for (int j = 0; j + 1 < map_width; ++j) {

			//
			// FLOWER METHOD
			// GLfloat		midpoint = GLfloat(map[i][j]) + GLfloat(map[i + 1][j]) + GLfloat(map[i][j + 1]) + GLfloat(map[i + 1][j + 1]);
			// midpoint /= 4.0f;
			// form_triangles(midpoint, i, j, (width * i + j) * 72, map);
			//FLOWER METHOD ENDS
			//

			form_triangles((GLfloat)map_height, i, j, count * 18, map);
			count++;
		}
	}
}

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

OPENGL_stuff::OPENGL_stuff(std::string heightmap_path): map(heightmap_path), buffer(map.data, map.width, map.height) {

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

	std::ifstream ifs("shaders/vertex_shader.vert");
	std::string		content( (std::istreambuf_iterator<char>(ifs)),
							 (std::istreambuf_iterator<char>()));
	GLuint			vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	auto			content_pointer = content.data();
	glShaderSource(vertex_shader, 1, &content_pointer, NULL);
	glCompileShader(vertex_shader);
	GLint		success;
	GLchar		infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "COMPILATION FAILED!\n" << infoLog << std::endl;
	}
	GLuint			fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::ifstream ifs_frag("shaders/fragment_shader.frag");
	std::string		content_frag( (std::istreambuf_iterator<char>(ifs_frag)),
							 (std::istreambuf_iterator<char>()));
	auto			content_frag_pointer = content_frag.data();
	glShaderSource(fragment_shader, 1, &content_frag_pointer, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "COMPILATION FAILED!\n" << infoLog << std::endl;
	}
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "PROGRAM LINK FAILED\n" << infoLog << std::endl;
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, buffer.vertex_count * 3 * 3 * sizeof(GLfloat), buffer.vertex_list, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glUseProgram(shader_program);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, buffer.vertex_count * 9 * sizeof(GLfloat), buffer.vertex_list, GL_STATIC_DRAW);
	glVertexAttribPointer(0, buffer.vertex_count, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

OPENGL_stuff::~OPENGL_stuff() {
	// glfwDestroyWindow(window);
}

void			OPENGL_stuff::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat	time_value = glfwGetTime();
		GLfloat water_level = (sin(time_value * 3) / 2) + 0.5;
		glUseProgram(shader_program);
		GLint	vertex_water_level_location = glGetUniformLocation(shader_program, "water_level");
		glUniform1f(vertex_water_level_location, water_level);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, buffer.vertex_count * 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
