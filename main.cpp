#include "terrain.hpp"

class HelloTriangleApplication
{
public:
	void run()
	{
		init_window();
		init_vulkan();
		main_loop();
		cleanup();
	}

private:
	GLFWwindow*	window;
	VkInstance	instance;

	void enumerate_instances()
	{
		uint32_t	extension_count = 0;

		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

		std::vector<VkExtensionProperties> extensions(extension_count);
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
		std::cout << "available extensions" << std::endl;
		for (const auto &extension: extensions)
			std::cout << "\t" << extension.extensionName << std::endl;
	}

	bool check_validation_layer_support()
	{
		uint32_t	layer_count;
		vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

		std::vector<VkLayerProperties> available_layers(layer_count);
		vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
		for (const char* layer_name : validation_layers)
		{
			bool layer_found = false;

			for (const auto& layer_properties: available_layers)
			{
				if (strcmp(layer_name, layer_properties.layerName) == 0)
				{
					layer_found = true;
					break;
				}
			}

			if (!layer_found)
				return false;
		}
		return true;
	}

	std::vector<const char*> get_required_extensions()
	{
		uint32_t	glfw_extension_count = 0;
		const char	**glfw_extensions;

		glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
		std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);
		if (enable_validation_layers)
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		return (extensions);
	}

	void create_instance()
	{
		VkApplicationInfo app_info = {};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Hello Triangle";
		app_info.applicationVersion = VK_MAKE_VERSION(1, 1, 0);
		app_info.pEngineName = "No Engine";
		app_info.engineVersion = VK_MAKE_VERSION(1, 1, 0);
		app_info.apiVersion = VK_MAKE_VERSION(1, 1, 0);

		VkInstanceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		if (enable_validation_layers && !check_validation_layer_support())
			throw std::runtime_error("validation layers requested, but not available!");
		check_validation_layer_support();
		if (enable_validation_layers)
		{
			create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
			create_info.ppEnabledLayerNames = validation_layers.data();
		}
		else
			create_info.enabledLayerCount = 0;

		auto extensions = get_required_extensions();
		create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		create_info.ppEnabledExtensionNames = extensions.data();
		#ifdef PRINT
			enumerate_instances();
		#endif
		VkResult result;
		if ((result = vkCreateInstance(&create_info, nullptr, &instance)) != VK_SUCCESS)
		{
			printf("%d\n", result);
			throw std::runtime_error("failed to create instance!");
		}
	}

	void init_vulkan()
	{
		create_instance();
		// setup_debug_callback();
		// pick_physical_device();
	}

	void init_window()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Terrain", nullptr, nullptr);
	}

	void main_loop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

int main()
{
	HelloTriangleApplication app;

	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
