#include "Line.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

Line::Line(float startingPoint[2], float endingPoint[2]){
	glGenVertexArrays(1, &(VAO));
	glGenBuffers(1, &VBO);
	
	unsigned const int vertexDataCount = 6;
	float vertexData[vertexDataCount]  {startingPoint[0], startingPoint[1], 0.5,
				endingPoint[0], endingPoint[1], 0.5 };
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertexDataCount, vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 Pos;\n"
            "void main() {\n"
            "   gl_Position = vec4(Pos.x, Pos.y, Pos.z, 1.0);}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "void main(){\n"
            "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);}\n\0";
		// Creating Shaders
	

	GLint succes;
	GLchar infoLog[512];
	GLuint fragment;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, (const GLchar**)&fragmentShaderSource, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if(!succes)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		fprintf(stderr, "FATAL. COULDNT COMPILE FRAGMENT SHADER %s\n", infoLog);
		exit(EXIT_FAILURE);
	}


	GLuint vertex;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, (const GLchar**)&vertexShaderSource, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if(!succes)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		fprintf(stderr, "FATAL. COULDNT COMPILE VERTEX SHADER %s\n", infoLog);
		exit(EXIT_FAILURE);
	}
	
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succes);
	if(!succes)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "FATAL. COULDNT LINK SHADER PROGRAM %s\n", infoLog);
		exit(EXIT_FAILURE);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// Disabling buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::Draw(void){
	glUseProgram(shaderProgram);

	glBindVertexArray(VAO);
	
	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
}
