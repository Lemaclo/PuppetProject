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
	checkCompileErrors(vertex, "VERTEX");
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1,  &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(vertex, "FRAGMENT");
	// Juntamos en el programa final
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	//checkCompileErrors(vertex, "PROGRAM");
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
void Shader::setMat4(const string &name, const glm::mat4 &val){
	unsigned int transformLoc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &val[0][0]);
}

// Lo siento, es copia directa del LearnOpenGL. Necesito ver los errores.
// utility function for checking shader compilation/linking errors.
void Shader::checkCompileErrors(GLuint shader, string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
	    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	    if (!success)
	    {
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	    }
	}
	else
	{
	    glGetProgramiv(shader, GL_LINK_STATUS, &success);
	    if (!success)
	    {
		glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	    }
	}
}
