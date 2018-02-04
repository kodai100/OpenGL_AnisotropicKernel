#include <iostream>
#include <algorithm>
#include <vector>
#include <GLFW\glfw3.h>

#include "Vector2f.h"
#include "Matrix2f.h"
#include "SimConstants.h"
#include "GLFWUtil.h"
#include "GLUtil.h"
#include "ParticleDrawer.h"
#include "AnisotropicKernel.h"

using namespace std;
using namespace SurfaceReconstruction;


void init_particle(vector<Vector2f>& particles) {

	for (int i = 0; i < particles.size(); i++) {
		float x = 0.8 * (2 * (float)rand() / RAND_MAX - 1);
		float y = 0.8 * (2 * (float)rand() / RAND_MAX - 1);
		particles[i].setData(x, y);
	}
}

int main() {

	GLFWwindow* window = GLFWUtil::initGLFWContext("Particle Drawer", WIN_X, WIN_Y);

	GLUtil::initGLContext(WIN_X, WIN_Y);

	vector<Vector2f> particle(num_particles);
	init_particle(particle);

	// Create transformation matrix array
	vector<Vector2f> new_pos(num_particles);
	vector<Matrix2f> matrices = AnisotropicKernel::calc(particle, new_pos);


	while (glfwWindowShouldClose(window) == GL_FALSE) {

		glClear(GL_COLOR_BUFFER_BIT);

		ParticleDrawer::transformed_circle(matrices, new_pos, 0.08f, 24);
		// ParticleDrawer::dot(particle, 2);
		// ParticleDrawer::circle(particle, 0.02f, 24);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}