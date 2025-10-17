#include <iostream>
#include <cmath>
#include <vector>
#include "include/glad/glad.h"
#include "include/shaderClass.hpp"
#include "include/cubeClass.hpp"
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

    /*
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
    */

    // Creamos las primitivas 

    Cube head(1.0f, 1.0f, 1.0f); // Cabeza
    Cube torso(3.0f, 5.0f, 2.0f); // Torso
    Cube left_arm(5.0f, 0.5f, 0.5f); // Brazo izquierdo
    Cube right_arm(5.0f, 0.5f, 0.5f); // Brazo derecho
    Cube left_leg(0.5f, 6.5f, 0.7f); // Pierna izquierda
    Cube right_leg(0.5f, 6.5f, 0.7f); // Pierna derecha
    torso.translate(glm::vec3(0.0f,-3.0f,0.0f));
    left_arm.translate(glm::vec3(-2.6f,-1.5f,0.0f));
    right_arm.translate(glm::vec3(2.6f,-1.5f,0.0f));
    left_leg.translate(glm::vec3(-1.0f,-7.3f,0.0f));
    right_leg.translate(glm::vec3(1.0f,-7.3f,0.0f));

    // Shaders (La clase abstrae la parte de compilar, linkear, y juntar todo)
    //Shader greenTime("Shaders/greenTime.vs", "Shaders/greenTime.fs");
    //Shader color("Shaders/color.vs", "Shaders/color.fs");
    Shader rot("Shaders/rotation.vs", "Shaders/rotation.fs");

    // Configuramos los vertex attributes
    // Posicion
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // Color
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    //glEnableVertexAttribArray(1);

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

    // Z - Buffer, para que no se dibuje algo atras por delante.
    glEnable(GL_DEPTH_TEST);

    // Matriz de proyeccion con perspectiva
    glm:: mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    float x_offset = 0.0f, y_offset = 0.0f, z_offset = -5.0f;
    float x_ang = 0.0f, y_ang = 0.0f, z_ang = 0.0f;
    int state_a, state_d, state_w, state_s, state_q, state_e,
	state_n, state_i, state_p;

    float piece_ang = 0.1f;
    int cur_piece = 0;
    Cube* control[] = {&left_arm, &right_arm, &left_leg, &right_leg};
    bool chang = true;

    while(!glfwWindowShouldClose(window)){
	    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    // Recibimos input del usuario
	    state_a = glfwGetKey(window, GLFW_KEY_A);
	    state_d = glfwGetKey(window, GLFW_KEY_D);
	    state_w = glfwGetKey(window, GLFW_KEY_W);
	    state_s = glfwGetKey(window, GLFW_KEY_S);
	    state_q = glfwGetKey(window, GLFW_KEY_Q);
	    state_e = glfwGetKey(window, GLFW_KEY_E);
	    state_n = glfwGetKey(window, GLFW_KEY_N);
	    state_i = glfwGetKey(window, GLFW_KEY_I);
	    state_p = glfwGetKey(window, GLFW_KEY_P);

	    if(state_a == GLFW_PRESS) x_offset += 0.1f;
	    if(state_d == GLFW_PRESS) x_offset -= 0.1f;
	    if(state_q == GLFW_PRESS) y_offset += 0.1f;
	    if(state_e == GLFW_PRESS) y_offset -= 0.1f;
	    if(state_w == GLFW_PRESS) z_offset += 0.1f;
	    if(state_s == GLFW_PRESS) z_offset -= 0.1f;
	    if(state_n == GLFW_PRESS && chang){
		    piece_ang = 0.0f;
		    cur_piece++;
		    cur_piece %= 4;
		    chang = false;
	    }
	    if(state_i == GLFW_PRESS){
		    piece_ang += 0.1f;
		    chang = true;
	    }
	    if(state_p == GLFW_PRESS){
		    piece_ang -= 0.1f;
		    chang = true;
	    }

	    glm::mat4 view = glm::mat4(1.0f);
	    view = glm::translate(view, glm::vec3(0.0f, 3.0f, z_offset));

	    rot.use();

	    if(cur_piece < 2){
		    (*control[cur_piece]).rotate(piece_ang, glm::vec3(0.0f, 1.0f, 0.0f));
	    } else {
		    (*control[cur_piece]).rotate(piece_ang, glm::vec3(1.0f, 0.0f, 0.0f));
	    }


	    head.draw(rot);
	    torso.draw(rot);
	    left_arm.draw(rot);
	    right_arm.draw(rot);
	    left_leg.draw(rot);
	    right_leg.draw(rot);

	    glm::mat4 model = glm::mat4(1.0f);
	    view = glm::rotate(view, y_offset, glm::vec3(0.0f, 1.0f, 0.0f));
	    view = glm::rotate(view, x_offset, glm::vec3(1.0f, 0.0f, 0.0f));

	    rot.setMat4("model", model);
	    rot.setMat4("view", view);
	    rot.setMat4("projection", projection);

	    /*
	    glBindVertexArray(VAO1);
	    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	    glBindVertexArray(0);

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

