cmake_minimum_required(VERSION 3.16.3)
project(main)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wextra -Wall -g
	)

add_executable(exec main.cpp
		Line.cpp
	)
target_link_libraries(exec
	-lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lm
		)

target_link_directories(exec
	PUBLIC -I/usr/include/GLFW/glfw3.h
		)

