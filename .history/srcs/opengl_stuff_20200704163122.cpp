#include "terrain.hpp"

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

void	camera_class::compute_camera_matrix() {
	update_right_and_upper();
	cam_matrix = glm::lookAt(position, position + direction, upper_dir);
}

void	camera_class::update_right_and_upper() {
	right_dir = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
	upper_dir = glm::normalize(glm::cross(direction, right_dir));
}

camera_class::camera_class(int right, int up) {
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	position = glm::vec3(float(right) / 2.0f, float(up) / 2.0f, 200.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	compute_camera_matrix();
	projection = glm::perspective(glm::radians(80.0f), float(width) / (float)height, 0.1f, 1000.0f);
}

GLuint	OPENGL_stuff::create_shader_program(std::string vertex_shader_src, std::string fragment_shader_src) {
	std::ifstream ifs(vertex_shader_src);
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
	std::ifstream ifs_frag(fragment_shader_src);
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
	auto new_shader_program = glCreateProgram();
	glAttachShader(new_shader_program, vertex_shader);
	glAttachShader(new_shader_program, fragment_shader);
	glLinkProgram(new_shader_program);
	glGetProgramiv(new_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(new_shader_program, 512, NULL, infoLog);
		std::cout << "PROGRAM LINK FAILED\n" << infoLog << std::endl;
	}
	return (new_shader_program);
}

OPENGL_stuff::OPENGL_stuff(std::string heightmap_path): map(heightmap_path), buffer(map.data, map.width, map.height), camera(map.width, map.height) {

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
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetCursorPosCallback(window, move_callback);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader_program = create_shader_program("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, buffer.vertex_count * 3 * 3 * sizeof(GLfloat), buffer.vertex_list, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	water_program = create_shader_program("shaders/water_shader.vert", "shaders/water_shader.frag");

	glGenVertexArrays(1, &WATER_VAO);
	glGenBuffers(1, &WATER_VBO);
	glBindVertexArray(WATER_VAO);

	auto null_map = new int*[map.height];
	for (int i = 0; i < map.height; ++i) {
		null_map[i] = new int[(map.width)];
		for (int j = 0; j < map.width; ++j) {
			null_map[i][j] = 0;
		}
	}
	auto water_buffer = vertex_buffer(null_map, int(map.width), int(map.height));
	glBindBuffer(GL_ARRAY_BUFFER, WATER_VBO);
	glBufferData(GL_ARRAY_BUFFER, water_buffer.vertex_count * 3 * 3 * sizeof(GLfloat), water_buffer.vertex_list, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	water_level = 0.0;
}

OPENGL_stuff::~OPENGL_stuff() {
	// glfwDestroyWindow(window);
}

void			OPENGL_stuff::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// GLfloat	time_value = glfwGetTime();
		// water_level = (sin(time_value * 3) / 2) + 0.5;
		glUseProgram(shader_program);

		GLint	vertex_water_level_location = glGetUniformLocation(shader_program, "water_level");
		glUniform1f(vertex_water_level_location, water_level);

		GLint	projection_matrix = glGetUniformLocation(shader_program, "projection");
		glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &camera.projection[0][0]);

		GLint	camera_matrix_location = glGetUniformLocation(shader_program, "camera");
		glUniformMatrix4fv(camera_matrix_location, 1, GL_FALSE, &camera.cam_matrix[0][0]);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, buffer.vertex_count * 3);
		glBindVertexArray(0);

		glUseProgram(water_program);

		vertex_water_level_location = glGetUniformLocation(water_program, "water_level");
		glUniform1f(vertex_water_level_location, water_level);

		projection_matrix = glGetUniformLocation(water_program, "projection");
		glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &camera.projection[0][0]);

		camera_matrix_location = glGetUniformLocation(water_program, "camera");
		glUniformMatrix4fv(camera_matrix_location, 1, GL_FALSE, &camera.cam_matrix[0][0]);

		glBindVertexArray(WATER_VAO);
		glDrawArrays(GL_TRIANGLES, 0, buffer.vertex_count * 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
