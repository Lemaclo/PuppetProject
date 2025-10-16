#ifndef CUBE
#define CUBE

#include "glad/glad.h"
#include "shaderClass.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

float vertices[] = {
	// Posicion x y z	 // Colores r g b
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f
};

unsigned int indices[]{
	0, 1, 3, // L
	0, 2, 3,
	4, 5, 7, // R
	4, 6, 7,
	7, 3, 2, // U
	7, 6, 2,
	5, 1, 0, // D
	5, 4, 0,
	5, 1, 3, // F
	5, 7, 3,
	4, 0, 2, // B
	4, 6, 2
};

struct Cube{
	unsigned int VAO, VBO, EBO;
	glm::mat4 trans;
	Cube(float sx=1.0f, float sy=1.0f, float sz=1.0f);
	void draw(Shader &sh);
};

#endif

