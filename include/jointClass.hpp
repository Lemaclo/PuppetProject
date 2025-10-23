#ifndef JOINT
#define JOINT

#include "glad/glad.h"
#include "shaderClass.hpp"
#include "cubeClass.hpp"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Joint{
	Cube piece;
	bool selected;
	vector<Joint *> children;
	Joint(glm::vec3 scale, glm::vec3 art, glm::vec3 pos, glm::vec3 mag, glm::vec3 Mag);
	void add_children(Joint *j);
	void draw(glm::mat4 base, Shader &sh);
};

#endif


