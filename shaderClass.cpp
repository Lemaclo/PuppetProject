#include "shaderClass.hpp"

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile){
	// Leemos el contenido de los archivos
	string vertexCode, fragmentCode;
	ifstream vertexFile, fragmentFile;
	vertexFile.open(vertexShaderFile);
	fragmentFile.open(fragmentShaderFile);
	stringstream vertexStream, fragmentStream;
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();
	vertexFile.close();
	fragmentFile.close();
	vertexCode = vertexStream.str();
	fragmentCode = fragmentStream.str();
	// Estos son los strings que ya podemos usar
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// Creamos los shaders
	unsigned int vertex, fragment;
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1,  &vShaderCode, NULL);
	glCompileShader(vertex);
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1,  &fShaderCode, NULL);
	glCompileShader(fragment);
	// Juntamos en el programa final
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	// Borramos los shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

//Funciones de utilidad varias

void Shader::use(){
	glUseProgram(id);
}

// Para settear los unformes del shader. Supongo que eventualmente llenare esto con vecs
// conforme lo requiera
void Shader::setBool(const string &name, bool val){
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)val);
}
void Shader::setInt(const string &name, int val){
	glUniform1i(glGetUniformLocation(id, name.c_str()), val);
}
void Shader::setFloat(const string &name, float val){
	glUniform1f(glGetUniformLocation(id, name.c_str()), val);
}
