#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

int main() {
    // -- snip --
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 400, "Primera Tarea", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    cout << glGetString(GL_VERSION) << '\n';
    cout << glGetString(GL_VENDOR) << '\n';
    cout << glGetString(GL_RENDERER) << '\n';
    cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
	    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	    glClear( GL_COLOR_BUFFER_BIT );

	    // Draw nothing, see you in tutorial 2 !

	    // Swap buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		    glfwWindowShouldClose(window) == 0 );


    // Successfully loaded OpenGL
    //printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // -- snip --
}

