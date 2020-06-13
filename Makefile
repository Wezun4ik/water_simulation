# VULKAN_SDK_PATH = /home/ilya/vulkan/1.1.130.0/x86_64

CFLAGS = -std=c++17 -Wall -Wextra -I./includes/ -g
ifeq ($(detected_OS),Linux)
 LDFLAGS =  LDFLAGS =  -L/usr/lib64 `pkg-config --static --libs glfw3` `pkg-config --static --libs glew`  `pkg-config --libs opencv` #for Linux
 else
 LDFLAGS = -framework OpenGL `pkg-config --static --libs glfw3` `pkg-config --static --libs glew` #for MAcOS
 endif
# LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
NAME = terrain
SRCS =	main.cpp\
		opengl_stuff.cpp\
		heightmap.cpp
SRCS_DIR = ./srcs
SRC_LIST = $(addprefix $(SRCS_DIR)/, $(SRCS))

$(NAME): $(SRC_LIST)
	g++ $(CFLAGS) -o $(NAME) $(SRC_LIST) $(LDFLAGS)
.PHONY: clean

clean:
	rm -f $(NAME)

re: clean $(NAME)
