/*
 * Esta clase abstrae todo el proceso de creacion de los shaders.
 * Implementa un constructor que lee los shaders de archivos, los
 * compila, y los linkea al programa princial.
 * Algo que no hice fue que escupa los errores de compilacion de los shaders.
 */
#ifndef SHADER
#define SHADER

#include "glad/glad.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Shader{
	//id unico del programa shader
	unsigned int id;
	// Constructor que lee de archivos
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	// Para usar el shader
	void use();
	// Para settear parametros uniformes. Util para interactuar con el programa
	void setBool(const string &name, bool val);
	void setInt(const string &name, int val);
	void setFloat(const string &name, float val);
	void setMat4(const string &name, const glm::mat4 &val);
};

#endif
