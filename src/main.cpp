#include "Line.hpp"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define WINDOW_HEIGHT 600.0f
#define WINDOW_WIDTH 800.0f

// Defining various callbacks

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cerr<<"Xpos = "<<xpos<<std::endl;
}


int main()
{

	// Setting up glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *mainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Platform v0.01", NULL, NULL );
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwSetWindowAttrib(mainWindow, GLFW_FLOATING, GLFW_TRUE);
	glfwSetWindowSize(mainWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwRestoreWindow(mainWindow);

	if (mainWindow == NULL)
	{
		fprintf(stderr, "Failed to create GLFWwindow! Aborting. \n");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(mainWindow);

	glfwSetCursorPosCallback(mainWindow, cursor_position_callback);

	// Setting up glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize glew! Aborting. \n");
		exit(EXIT_FAILURE);
	}
	float startingPoint[2] = {0.0f, 0.0f};
	float endingPoint[2] = {-1.0f, -1.0f};
	Line testLine(startingPoint, endingPoint);


	while(!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();
		// Setting clear color
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Gray color
		glClear(GL_COLOR_BUFFER_BIT);
		testLine.Draw();
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}


