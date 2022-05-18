#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Line{
	public:
		//~Line();
		Line(float startingPoint[2], float endingPoint[2]);
		void Draw(void);
	private:
		float x;
		float y;
		GLuint VAO;
		GLuint VBO;
		GLuint shaderProgram;
};
