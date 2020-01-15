VULKAN_SDK_PATH = /home/ilya/vulkan/1.1.130.0/x86_64

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -Wall -Wextra -Werror
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
NAME = terrain

$(NAME): main.cpp
	g++ $(CFLAGS) -o $(NAME) main.cpp $(LDFLAGS)
.PHONY: test clean

test: $(NAME)
	@LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib
		@VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d
		./$(NAME)

clean:
	rm -f VulkanTest
