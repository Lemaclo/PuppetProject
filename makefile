main : main.cpp
	g++ main.cpp glad.c include/shaderClass.cpp include/cubeClass.cpp -Llib -lglad -lglfw
