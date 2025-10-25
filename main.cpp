#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <stack>
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

// Para hacer undo / redo
stack<pair<Joint *, glm::vec3>> undo_stack, redo_stack;

// Crea los Joints necesarios para la marioneta e inicializa la camara.
// Lee de un archivo los datos necesarios para las primitivas.
void init(string file){
	camara_pos = glm::vec3(0.0f, 0.4f, -30.0f);
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
		float mx, Mx, my, My, mz, Mz; f >> mx >> Mx >> my >> My >> mz >> Mz;
		mx = glm::radians(mx); Mx = glm::radians(Mx);
		my = glm::radians(my); My = glm::radians(My);
		mz = glm::radians(mz); Mz = glm::radians(Mz);
		// Creamos los Joints con memoria dinamica
		puppet.push_back(new Joint(glm::vec3(sx,sy,sz), glm::vec3(cx,cy,cz), 
					glm::vec3(px,py,pz), glm::vec3(mx, my, mz), 
					glm::vec3(Mx,My,Mz)));
	}
	// Establecemos las relaciones de jerarquia.
	for(int i=1;i<n;i++){
		int u, v; f >> u >> v;
		u--; v--;
		puppet[u]->add_children(puppet[v]);
	}
	cur_piece = 8; // La pieza 8 es la pelvis, la raiz del modelo
	puppet[cur_piece]->selected = true;
	f.close();
}

// Esta funcion maneja todo el input. 
void handle_input(GLFWwindow *window, int key, int scancode, int action, int mods){
	float d = 0.0f; // Con este valor cambian los angulos de la articulacion actual
	if(action == GLFW_PRESS) d = 0.1f;
	if(action == GLFW_RELEASE) d = -0.1f;
	switch(key){
		// Giramos nuestro punto de vista con las flechas
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
		// Movemos la camara
		case GLFW_KEY_W:
			camara_pos_delta.z += d;
			break;
		case GLFW_KEY_S:
			camara_pos_delta.z -= d;
			break;
		case GLFW_KEY_Q:
			camara_pos_delta.x += d;
			break;
		case GLFW_KEY_E:
			camara_pos_delta.x -= d;
			break;
		case GLFW_KEY_A:
			camara_pos_delta.y += d;
			break;
		case GLFW_KEY_D:
			camara_pos_delta.y -= d;
			break;
		// Ciclamos de articulacion seleccionada
		case GLFW_KEY_N:
			if(action == GLFW_PRESS){
			    puppet[cur_piece]->selected = false;
			    cur_piece++;
			    cur_piece %= puppet.size();
			    puppet[cur_piece]->selected = true;
			    piece_ang = puppet[cur_piece]->piece.ang;
			}
			break;
		// Regresamos
		case GLFW_KEY_M:
			if(action == GLFW_PRESS){
			    puppet[cur_piece]->selected = false;
			    cur_piece--;
			    if(cur_piece < 0) cur_piece = puppet.size() - 1;
			    puppet[cur_piece]->selected = true;
			    piece_ang = puppet[cur_piece]->piece.ang;
			}
			break;
		// Seleccionamos la pelvis (todo el modelo)
		case GLFW_KEY_B:
			if(action == GLFW_PRESS){
			    puppet[cur_piece]->selected = false;
			    cur_piece = 8; // Pelvis, root
			    piece_ang = puppet[cur_piece]->piece.ang;
			}
			break;
		// Reiniciamos la articulacion seleccionada
		case GLFW_KEY_R:
			piece_ang = glm::vec3(0.0f, 0.0f, 0.0f);
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		// Reiniciamos la camara
		case GLFW_KEY_X:
			camara_pos = glm::vec3(0.0f, 0.4f, -30.0f);
			camara_ang = glm::vec3(0.0f, 0.0f, 0.0f);
			camara_pos_delta = glm::vec3(0.0f, 0.0f, 0.0f);
			camara_ang_delta = glm::vec3(0.0f, 0.0f, 0.0f);
			break;
		// Giramos la articulacion actual
		case GLFW_KEY_I:
			while(!redo_stack.empty()) redo_stack.pop();
			piece_ang_delta.x += d;
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		case GLFW_KEY_P:
			while(!redo_stack.empty()) redo_stack.pop();
			piece_ang_delta.x -= d;
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		case GLFW_KEY_J:
			while(!redo_stack.empty()) redo_stack.pop();
			piece_ang_delta.y += d;
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		case GLFW_KEY_L:
			while(!redo_stack.empty()) redo_stack.pop();
			piece_ang_delta.y -= d;
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		case GLFW_KEY_O:
			while(!redo_stack.empty()) redo_stack.pop();
			piece_ang_delta.z += d;
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		case GLFW_KEY_K:
			while(!redo_stack.empty()) redo_stack.pop();
			piece_ang_delta.z -= d;
			if(action == GLFW_PRESS){
				undo_stack.push(make_pair(puppet[cur_piece], puppet[cur_piece]->piece.ang));
			}
			break;
		// Undo
		case GLFW_KEY_U:
			if(action == GLFW_PRESS && !undo_stack.empty()){
				Joint *j = undo_stack.top().first;
				glm::vec3 a = undo_stack.top().second;
				redo_stack.push(make_pair(j, j->piece.ang));
				if(puppet[cur_piece] == j){
					piece_ang = a;
				} else {
					j->piece.set_angles(a);
				}
				undo_stack.pop();

			}
			break;
		case GLFW_KEY_Y: //Redo
			if(action == GLFW_PRESS && !redo_stack.empty()){
				Joint *j = redo_stack.top().first;
				glm::vec3 a = redo_stack.top().second;
				undo_stack.push(make_pair(j, j->piece.ang));
				if(puppet[cur_piece] == j){
					piece_ang = a;
				} else {
					j->piece.set_angles(a);
				}
				redo_stack.pop();

			}
			break;
		case GLFW_KEY_H: //Reset Global
			while(!undo_stack.empty()) undo_stack.pop();
			while(!redo_stack.empty()) redo_stack.pop();
			for(Joint *j : puppet){
				glm::vec3 t = glm::vec3(0.0f,0.0f,0.0f);
				j->piece.set_angles(t);
			}
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

    // Inicializamos la camara, y las posiciones.
    init("puppet.txt");
    //init("free_puppet.txt");
    
    // Configuramos la funcion de input
    glfwSetKeyCallback(window, handle_input);

    while(!glfwWindowShouldClose(window)){
	    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    // Actualizamos los angulos y posicinoes de la camara
	    camara_pos += camara_pos_delta;
	    camara_ang += camara_ang_delta;

	    piece_ang += piece_ang_delta;

	    // Con esto, controlamos la camara. Es importante el orden de las matrices.
	    glm::mat4 view = glm::mat4(1.0f);
	    view = glm::rotate(view, camara_ang.x, glm::vec3(1.0f, 0.0f, 0.0f));
	    view = glm::rotate(view, camara_ang.y, glm::vec3(0.0f, 1.0f, 0.0f));
	    view = glm::rotate(view, camara_ang.z, glm::vec3(0.0f, 0.0f, 1.0f));
	    view = glm::translate(view, camara_pos);

	    // Usamos el mismo shader siempre
	    rot.use();

	    // Estas matrices no dependen de la articulacion.
	    rot.setMat4("view", view);
	    rot.setMat4("projection", projection);

	    // Actualizamos los angulos de la pieza actual
	    puppet[cur_piece]->piece.set_angles(piece_ang);

	    // Si el movimiento no tuvo efecto, lo quitamos de la pila de undo
	    if(!undo_stack.empty() && 
			    undo_stack.top().first == puppet[cur_piece] && 
			    undo_stack.top().second == puppet[cur_piece]->piece.ang){
		    undo_stack.pop();
	    }

	    // Dibujamos (de manera recursiva) la articulacion padre de todos.
	    puppet[8]->draw(glm::mat4(1.0f), rot);

	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } 
    // Liberamos la memoria dinamica y cerramos
    for(Joint *j : puppet) delete j;
    glfwTerminate();
    return 0;
}

