# VULKAN_SDK_PATH = /home/ilya/vulkan/1.1.130.0/x86_64

CFLAGS = -std=c++17 -Wall -Wextra -lSDL2 -I./includes/
# LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
NAME = terrain

$(NAME): main.cpp
	g++ $(CFLAGS) -o $(NAME) main.cpp
.PHONY: clean

clean:
	rm -f $(NAME)
