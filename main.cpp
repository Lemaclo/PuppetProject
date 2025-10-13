#include <iostream>
#include <cmath>
#include "include/glad/glad.h"
#include "shaderClass.hpp"
#include <GLFW/glfw3.h>

using namespace std;

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "PUPPET", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    // Pasos de LearnOpenGl
    float vertices1[] = {
	    -0.5f, -0.5f, 0.0f,
	     0.0f, -0.5f, 0.0f,
	     -0.5f,  0.5f, 0.0f
    };

    float vertices2[] = {
	    0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    //Vertex Array Object 
    unsigned int VAO1, VAO2;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    unsigned int VBO1, VBO2; //Vertex Buffer
    glGenBuffers(1, &VBO1); // Lo generamos
    glBindBuffer(GL_ARRAY_BUFFER, VBO1); // Lo seleccionamos
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW); // Le metemos los datos
    // Vertex Shader Basico
    /*
    const char *vertexShaderSource1 = "# version 460 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
	*/
    const char *vertexShaderSource2 = "# version 460 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 myColor;\n"
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"myColor = aColor;\n"
	"}\0";
    unsigned int vertexShader1, vertexShader2;
    /*
    vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader1, 1, &vertexShaderSource1, NULL);
    glCompileShader(vertexShader1);
    */
    vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);
    // Fragment Shader Basico
    /*
    const char *fragmentShaderSource1 = "# version 460 core\n"
	    "out vec4 FragColor;\n"
	    "uniform vec4 ourColor;\n"
	    "void main()\n"
	    "{\n"
	    "FragColor = ourColor;\n"
	    "}\0";
    */
    const char *fragmentShaderSource2 = "# version 460 core\n"
	    "out vec4 FragColor;\n"
	    "in vec3 myColor;\n"
	    "void main()\n"
	    "{\n"
	    "FragColor = vec4(myColor, 1.0f);\n"
	    "}\0";
    unsigned int fragmentShader1, fragmentShader2;
    //fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    // Shader Program (Juntamos ambos shaders)
    Shader greenTime("greenTime.vs", "greenTime.fs");
    unsigned int shaderProgram1, shaderProgram2;
    /*
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader1);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    */
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    //glDeleteShader(vertexShader1);
    glDeleteShader(vertexShader2);
    //glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    // Configuramos los vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Vertex Array Object 
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glGenBuffers(1, &VBO2); // Lo generamos
    glBindBuffer(GL_ARRAY_BUFFER, VBO2); // Lo seleccionamos
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); // Le metemos los datos
    // Atributo de pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    while(!glfwWindowShouldClose(window)){
	    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	    glClear( GL_COLOR_BUFFER_BIT );
	    //glUseProgram(shaderProgram1);
	    greenTime.use();
	    float timeValue = glfwGetTime();
	    float greenVal = sin(timeValue) / 2.0f + 0.5f;
	    /*
	    int vertexColorLocation = glGetUniformLocation(shaderProgram1, "ourColor");
	    glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);
	    */
	    greenTime.setFloat("ourColor", greenVal);

	    glBindVertexArray(VAO1);
	    glDrawArrays(GL_TRIANGLES, 0, 3);

	    glUseProgram(shaderProgram2);
	    glBindVertexArray(VAO2);
	    glDrawArrays(GL_TRIANGLES, 0, 3);
	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } 
    glfwTerminate();
    return 0;
}

