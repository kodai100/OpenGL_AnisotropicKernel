#pragma once

#include <iostream>
#include <GLFW\glfw3.h>

using namespace std;

class GLFWUtil {
public:
	static GLFWwindow* initGLFWContext(string window_name, int width, int height);
};



GLFWwindow* GLFWUtil::initGLFWContext(string window_name, int width, int height) {
	if (glfwInit() == GL_FALSE) {
		cerr << "Can't initilize GLFW" << endl;
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
	if (window == nullptr) {
		cerr << "Can't create GLFW window." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	return window;
}