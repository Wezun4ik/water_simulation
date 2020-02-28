# VULKAN_SDK_PATH = /home/ilya/vulkan/1.1.130.0/x86_64

CFLAGS = -std=c++17 -Wall -Wextra -I./includes/
LDFLAGS = -lSDL2
# LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
NAME = terrain

$(NAME): main.cpp
	g++ $(CFLAGS) -o $(NAME) main.cpp $(LDFLAGS)
.PHONY: clean

clean:
	rm -f $(NAME)
