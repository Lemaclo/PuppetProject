#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "PUPPET", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    // Pasos de LearnOpenGl
    float vertices[] = {
	    -0.5f, -0.5f, 0.0f,
	     0.5f, -0.5f, 0.0f,
	     0.0f,  0.5f, 0.0f
    };

    //Vertex Array Object 
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO; //Vertex Buffer
    glGenBuffers(1, &VBO); // Lo generamos
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Lo seleccionamos
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Le metemos los datos
    // Vertex Shader Basico
    const char *vertexShaderSource = "# version 460 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Fragment Shader Basico
    const char *fragmentShaderSource = "# version 460 core\n"
	    "out vec4 FragColor;\n"
	    "void main()\n"
	    "{\n"
	    "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
	    "}\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader Program (Juntamos ambos shaders)
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Configuramos los vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while(!glfwWindowShouldClose(window)){
	    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	    glClear( GL_COLOR_BUFFER_BIT );
	    glUseProgram(shaderProgram);
	    glBindVertexArray(VAO);
	    glDrawArrays(GL_TRIANGLES, 0, 3);
	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } 
    glfwTerminate();
    return 0;
}

