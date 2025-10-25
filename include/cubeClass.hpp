/* 
 * Esta clase define las primitivas de cubo y metodos auxiliares para modificarlas.
 * Abstrae todo lo relacionado a los Vertex Buffers y Vertex Arraya
 */
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
	glm::vec3 ang, min_ang, max_ang; // Angulos de Euler
	glm::vec3 s; // Escala de la primitiva
	glm::vec3 c; // Punto de "union" en articulacion. (en -0.5, 0.5)
	glm::vec3 pos; // Posicion del punto union
	glm::mat4 trans, base; // Matriz de transformacion local
	Cube();
	Cube(glm::vec3 _s, glm::vec3 _c, glm::vec3 mag, glm::vec3 Mag);
	void draw(Shader &sh); //Dibuja la primitiva
	// Rota y mueve la primitiva.
	void set_pos(glm::vec3 t);
	void translate(glm::vec3 t);
	void set_angles(glm::vec3 &t);
	void rotate(glm::vec3 t);
};

#endif

