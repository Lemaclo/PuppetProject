main : main.cpp
	g++ main.cpp glad.c include/shaderClass.cpp include/cubeClass.cpp include/jointClass.cpp -Llib -lglad -lglfw
