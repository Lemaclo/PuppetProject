#ifndef CUBE
#define CUBE

#include "glad/glad.h"
#include "shaderClass.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Cube{
	unsigned int VAO, VBO, EBO;
	float ang, sx, sy, sz;
	glm::vec3 mov, axis;
	glm::mat4 trans;
	Cube(float _sx, float _sy, float _sz);
	void draw(Shader &sh);
	void translate(glm::vec3 t);
	void rotate(float _ang, glm::vec3 t);
};

#endif

