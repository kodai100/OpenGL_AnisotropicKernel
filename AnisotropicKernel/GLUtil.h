#pragma once

#include <GLFW\glfw3.h>

class GLUtil {
public:
	static void initGLContext(int width, int height);
	static void drawRect(float width);
};

void GLUtil::initGLContext(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(float)width / height, (float)width / height, -1.0f, 1.0f, 0.0f, 1.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GLUtil::drawRect(float width) {
	glBegin(GL_POLYGON);
	glColor3d(1, 1, 1);
	glVertex2d(-width, -width);
	glColor3d(0, 1, 0);
	glVertex2d(-width, width);
	glColor3d(0, 0, 1);
	glVertex2d(width, width);
	glColor3d(1, 0, 0);
	glVertex2d(width, -width);
	glEnd();
}