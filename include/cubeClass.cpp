#include "cubeClass.hpp"

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

Cube::Cube(glm::vec3 _s, glm::vec3 _c){
	s = _s;
	c = _c * s;
	ang = glm::vec3(0.0f, 0.0f, 0.0f);
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	trans = glm::mat4(1.0f);

	// Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer
	glGenBuffers(1, &VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	// Element Array Buffer
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Attributes: Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Cube::draw(Shader &sh){
	// Inicializamos la matriz de transformacion local.
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, pos);
	// trans = glm::translate(trans, c); // Deshacemos
	// Rotamos
	trans = glm::rotate(trans, ang.x, glm::vec3(1.0f,0.0f,0.0f));
	trans = glm::rotate(trans, ang.y, glm::vec3(0.0f,1.0f,0.0f));
	trans = glm::rotate(trans, ang.z, glm::vec3(0.0f,0.0f,1.0f));
	trans = glm::translate(trans, -1.0f * c); // Movemos poco
	trans = glm::scale(trans, s); // Escalamos
	sh.setMat4("model", trans);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cube::set_pos(glm::vec3 t){
	pos = t;
}

void Cube::translate(glm::vec3 t){
	pos += t;
}
void Cube::set_angles(glm::vec3 t){
	ang = t;
}
void Cube::rotate(glm::vec3 t){
	ang += t;
}
