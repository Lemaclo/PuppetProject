#ifndef SHADER
#define SHADER

#include "include/glad/glad.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

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
};

#endif
