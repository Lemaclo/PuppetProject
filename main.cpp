#include <iostream>
#include <cmath>
#include "include/glad/glad.h"
#include "shaderClass.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "PUPPET", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    // Pasos de LearnOpenGl

    /*
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
    */

    float vertices[] = {
	    // Position x y z	 
	    -0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f, 0.5f,
	    -0.5f, 0.5f, -0.5f,
	    -0.5f, 0.5f, 0.5f,
	    0.5f, -0.5f, -0.5f,
	    0.5f, -0.5f, 0.5f,
	    0.5f, 0.5f, -0.5f,
	    0.5f, 0.5f, 0.5f
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

    //Vertex Array Object 
    unsigned int VAO1, VAO2;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    unsigned int VBO1, VBO2; //Vertex Buffer
    glGenBuffers(1, &VBO1); // Lo generamos
    glBindBuffer(GL_ARRAY_BUFFER, VBO1); // Lo seleccionamos
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Le metemos los datos

    // Element Array Buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Shaders (La clase abstrae la parte de compilar, linkear, y juntar todo)
    //Shader greenTime("Shaders/greenTime.vs", "Shaders/greenTime.fs");
    //Shader color("Shaders/color.vs", "Shaders/color.fs");
    Shader rot("Shaders/rotation.vs", "Shaders/rotation.fs");

    // Configuramos los vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Vertex Array Object 
    /*
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
    */

    while(!glfwWindowShouldClose(window)){
	    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	    glClear(GL_COLOR_BUFFER_BIT);
	    /*
	    greenTime.use();
	    float timeValue = glfwGetTime();
	    float greenVal = sin(timeValue) / 2.0f + 0.5f;
	    greenTime.setFloat("ourColor", greenVal);
	    */

	    rot.use();
	    glm::mat4 trans = glm::mat4(1.0f);
	    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	    rot.setMat4("transform", trans);

	    glBindVertexArray(VAO1);
	    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	    glBindVertexArray(0);

	    /*
	    color.use();
	    float offset = sin(timeValue) / 3.0f;
	    color.setFloat("offset", offset);

	    glBindVertexArray(VAO2);
	    glDrawArrays(GL_TRIANGLES, 0, 3);
	    */

	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } 
    glfwTerminate();
    return 0;
}

