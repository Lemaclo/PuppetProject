#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include "include/glad/glad.h"
#include "include/shaderClass.hpp"
#include "include/cubeClass.hpp"
#include "include/jointClass.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;


// Configuracion de camara
glm::vec3 camara_pos, camara_pos_delta;
glm::vec3 camara_ang, camara_ang_delta;

// Configuracion de pieza
glm::vec3 piece_pos, piece_pos_delta;
glm::vec3 piece_ang, piece_ang_delta;

// Selector de piezas
int cur_piece;
vector<Joint *> puppet; 

void init(string file){
	camara_pos = glm::vec3(0.0f, 2.0f, -15.0f);
	camara_ang = glm::vec3(0.0f, 0.0f, 0.0f);
	camara_pos_delta = glm::vec3(0.0f, 0.0f, 0.0f);
	camara_ang_delta = glm::vec3(0.0f, 0.0f, 0.0f);
	piece_ang = glm::vec3(0.0f, 0.0f, 0.0f);
	piece_ang_delta = glm::vec3(0.0f, 0.0f, 0.0f);
	ifstream f(file);
	int n; f >> n;
	for(int i=0;i<n;i++){
		float sx,sy,sz; f >> sx >> sy >> sz;
		float cx,cy,cz; f >> cx >> cy >> cz;
		float px,py,pz; f >> px >> py >> pz;
		puppet.push_back(new Joint(glm::vec3(sx,sy,sz), glm::vec3(cx,cy,cz), glm::vec3(px,py,pz)));
	}
	for(int i=1;i<n;i++){
		int u, v; f >> u >> v;
		u--; v--;
		puppet[u]->add_children(puppet[v]);
	}
	f.close();
}


void handle_input(GLFWwindow *window, int key, int scancode, int action, int mods){
	float d = 0.0f;
	if(action == GLFW_PRESS) d = 0.1f;
	if(action == GLFW_RELEASE) d = -0.1f;
	switch(key){
		case GLFW_KEY_LEFT:
			camara_ang_delta.y -= d * 0.1f;
			break;
		case GLFW_KEY_RIGHT:
			camara_ang_delta.y += d * 0.1f;
			break;
		case GLFW_KEY_DOWN:
			camara_ang_delta.x += d * 0.1f;
			break;
		case GLFW_KEY_UP:
			camara_ang_delta.x -= d * 0.1f;
			break;
		case GLFW_KEY_W:
			camara_pos_delta.z += d;
			break;
		case GLFW_KEY_S:
			camara_pos_delta.z -= d;
			break;
		case GLFW_KEY_Q:
			camara_ang_delta.x += d / glm::length(camara_pos);
			break;
		case GLFW_KEY_E:
			camara_ang_delta.x -= d / glm::length(camara_pos);
			break;
		case GLFW_KEY_A:
			camara_ang_delta.y += d / glm::length(camara_pos);
			break;
		case GLFW_KEY_D:
			camara_ang_delta.y -= d / glm::length(camara_pos);
			break;
		case GLFW_KEY_Z:
			camara_ang_delta.z += d / glm::length(camara_pos);
			break;
		case GLFW_KEY_C:
			camara_ang_delta.z -= d / glm::length(camara_pos);
			break;
		case GLFW_KEY_N:
			if(action == GLFW_PRESS){
			    puppet[cur_piece]->selected = false;
			    cur_piece++;
			    cur_piece %= puppet.size();
			    piece_ang = puppet[cur_piece]->piece.ang;
			}
			break;
		case GLFW_KEY_R:
			piece_ang = glm::vec3(0.0f, 0.0f, 0.0f);
			break;
		case GLFW_KEY_X:
			camara_pos = glm::vec3(0.0f, 2.0f, -15.0f);
			camara_ang = glm::vec3(0.0f, 0.0f, 0.0f);
			camara_pos_delta = glm::vec3(0.0f, 0.0f, 0.0f);
			camara_ang_delta = glm::vec3(0.0f, 0.0f, 0.0f);
			break;

		case GLFW_KEY_I:
			piece_ang_delta.x += d;
			break;
		case GLFW_KEY_P:
			piece_ang_delta.x -= d;
			break;
		case GLFW_KEY_J:
			piece_ang_delta.y += d;
			break;
		case GLFW_KEY_L:
			piece_ang_delta.y -= d;
			break;
		case GLFW_KEY_O:
			piece_ang_delta.z += d;
			break;
		case GLFW_KEY_K:
			piece_ang_delta.z -= d;
			break;
	}
}

int main() {
    // Inicializamos la ventana.
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "PUPPET", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();


    // Cargamos y compilamos los shaders
    Shader rot("Shaders/rotation.vs", "Shaders/rotation.fs");
    
    // Z - Buffer, para que no se dibuje algo atras por delante.
    glEnable(GL_DEPTH_TEST);

    // Matriz de proyeccion con perspectiva
    glm:: mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

    cur_piece = 0;
    //puppet = {&torso, &head, &left_arm, &right_arm, &left_leg, &right_leg, &tail, &tail2};

    // Inicializamos la camara, y las posiciones.
    init("puppet.txt");
    // Configuramos la funcion de input
    glfwSetKeyCallback(window, handle_input);

    while(!glfwWindowShouldClose(window)){
	    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    camara_pos += camara_pos_delta;
	    camara_ang += camara_ang_delta;

	    piece_ang += piece_ang_delta;

	    glm::mat4 view = glm::mat4(1.0f);
	    view = glm::rotate(view, camara_ang.x, glm::vec3(1.0f, 0.0f, 0.0f));
	    view = glm::rotate(view, camara_ang.y, glm::vec3(0.0f, 1.0f, 0.0f));
	    view = glm::rotate(view, camara_ang.z, glm::vec3(0.0f, 0.0f, 1.0f));
	    view = glm::translate(view, camara_pos);

	    rot.use();

	    rot.setMat4("view", view);
	    rot.setMat4("projection", projection);

	    puppet[cur_piece]->piece.set_angles(piece_ang);
	    puppet[cur_piece]->selected = true;
	    puppet[0]->draw(glm::mat4(1.0f), rot);
	    /*
	    for(int i=0;i<puppet.size();i++){
		    if(i == cur_piece){
			    rot.setBool("select", true);
			    puppet[i]->set_angles(piece_ang);
		    } else {
			    rot.setBool("select", false);
		    }
		    if(i != 0){
			    puppet[i]->base = puppet[0]->trans * glm::scale(glm::mat4(1.0f), 
					    glm::vec3(1.0f/(puppet[0]->s.x), 1.0f/(puppet[0]->s.y), 
						    1.0f/(puppet[0]->s.z)));
		    }
		    puppet[i]->draw(rot);
	    }
	    */

	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } 
    for(Joint *j : puppet) delete j;
    glfwTerminate();
    return 0;
}

