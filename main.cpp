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
    // Inicializamos la ventana.
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "PUPPET", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Cargamos y compilamos los shaders
    Shader rot("Shaders/rotation.vs", "Shaders/rotation.fs");
    // Creamos las primitivas 
    Cube head(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -0.5f, 0.0f)); // Cabeza
    Cube torso(glm::vec3(3.0f, 5.0f, 2.0f), glm::vec3(0.0f,0.0f,0.0f)); // Torso
    Cube left_arm(glm::vec3(3.0f, 0.5f, 0.5f), glm::vec3(0.5f,0.0f,0.0f)); // Brazo izquierdo
    Cube right_arm(glm::vec3(3.0f, 0.5f, 0.5f), glm::vec3(-0.5f,0.0f,0.0f)); // Brazo derecho
    Cube left_leg(glm::vec3(0.5f, 6.5f, 0.7f), glm::vec3(0.0f,0.5f,0.0f)); // Pierna izquierda
    Cube right_leg(glm::vec3(0.5f, 6.5f, 0.7f), glm::vec3(0.0f,0.5f,0.0f)); // Pierna derecha
    // Posiciones iniciales
    head.set_pos(glm::vec3(0.0f, 2.6f, 0.0f));
    left_arm.set_pos(glm::vec3(-1.6f, 1.5f, 0.0f));
    right_arm.set_pos(glm::vec3(1.6f, 1.5f, 0.0f));
    left_leg.set_pos(glm::vec3(-1.0f, -2.6f, 0.0f));
    right_leg.set_pos(glm::vec3(1.0f, -2.6f, 0.0f));

    // Z - Buffer, para que no se dibuje algo atras por delante.
    glEnable(GL_DEPTH_TEST);

    // Matriz de proyeccion con perspectiva
    glm:: mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    float x_offset = 0.0f, y_offset = 0.0f, z_offset = -10.0f;
    float x_ang = 0.0f, y_ang = 0.0f, z_ang = 0.0f;
    int state_a, state_d, state_w, state_s, state_q, 
	state_e, state_n, state_i, state_p, state_j, state_l,
	state_o, state_k, state_r;
    int cur_piece = 0;
    bool chang = true;
    vector<Cube *> puppet = {&torso, &head, &left_arm, &right_arm, &left_leg, &right_leg};

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
	    state_j = glfwGetKey(window, GLFW_KEY_J);
	    state_l = glfwGetKey(window, GLFW_KEY_L);
	    state_o = glfwGetKey(window, GLFW_KEY_O);
	    state_k = glfwGetKey(window, GLFW_KEY_K);
	    state_r = glfwGetKey(window, GLFW_KEY_R);

	    if(state_a == GLFW_PRESS) x_offset += 0.1f;
	    if(state_d == GLFW_PRESS) x_offset -= 0.1f;
	    if(state_q == GLFW_PRESS) y_offset += 0.1f;
	    if(state_e == GLFW_PRESS) y_offset -= 0.1f;
	    if(state_w == GLFW_PRESS) z_offset += 0.1f;
	    if(state_s == GLFW_PRESS) z_offset -= 0.1f;
	    if(state_n == GLFW_PRESS && chang) {
		    cur_piece++;
		    cur_piece %= puppet.size();
		    x_ang = puppet[cur_piece]->ang.x;
		    y_ang = puppet[cur_piece]->ang.y;
		    z_ang = puppet[cur_piece]->ang.z;
		    chang = false;
	    }
	    if(state_n == GLFW_RELEASE) chang = true;

	    if(state_i == GLFW_PRESS) x_ang += 0.1f;
	    if(state_p == GLFW_PRESS) x_ang -= 0.1f;
	    if(state_j == GLFW_PRESS) y_ang += 0.1f;
	    if(state_l == GLFW_PRESS) y_ang -= 0.1f;
	    if(state_o == GLFW_PRESS) z_ang += 0.1f;
	    if(state_k == GLFW_PRESS) z_ang -= 0.1f;
	    if(state_r == GLFW_PRESS) x_ang = y_ang = z_ang = 0.0f;

	    glm::mat4 view = glm::mat4(1.0f);
	    view = glm::translate(view, glm::vec3(0.0f, 2.0f, z_offset));

	    rot.use();
	    for(int i=0;i<puppet.size();i++){
		    if(i == cur_piece){
			    rot.setBool("select", true);
			    puppet[i]->set_angles(glm::vec3(x_ang, y_ang, z_ang));
		    } else {
			    rot.setBool("select", false);
		    }
		    puppet[i]->draw(rot);
	    }

	    view = glm::rotate(view, y_offset, glm::vec3(0.0f, 1.0f, 0.0f));
	    view = glm::rotate(view, x_offset, glm::vec3(1.0f, 0.0f, 0.0f));

	    rot.setMat4("view", view);
	    rot.setMat4("projection", projection);

	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } 
    glfwTerminate();
    return 0;
}

