#define _USE_MATH_DEFINES

#include "ParticleDrawer.h"

#include <iostream>
#include <cmath>

void ParticleDrawer::circle(std::vector<Vector2f>& vertices, float radius, int resolution) {

	if (resolution < 3) {
		std::cerr << "Resolution must be over 3" << std::endl;
		return;
	}

	glColor3f(1, 1, 1);

	const float delta = (float) 2 * M_PI / resolution;

	for (int i = 0; i < vertices.size(); i++) {
		Vector2f center = vertices[i];
		
		glBegin(GL_POLYGON);
		glVertex2d(center[0], center[1]);
		
		for (int j = 0; j <= resolution; j++) {
			Vector2f offset(cos(delta * j), sin(delta * j));
			offset *= radius;
			
			Vector2f translated = center + offset;
			glVertex2d(translated[0], translated[1]);
			
		}

		glEnd();
	}

}

void ParticleDrawer::transformed_circle(std::vector<Matrix2f>& matrices, std::vector<Vector2f>& vertices, float radius, int resolution) {

	if (resolution < 3) {
		std::cerr << "Resolution must be over 3" << std::endl;
		return;
	} else if (matrices.size() != vertices.size()) {
		std::cerr << "the number of matrices and vertices is not matched" << std::endl;
		return;
	}

	glColor3f(0, 0.5, 0.5);

	const float delta = (float)2 * M_PI / resolution;

	for (int i = 0; i < vertices.size(); i++) {
		Vector2f center = vertices[i];

		glBegin(GL_POLYGON);
		glVertex2d(center[0], center[1]);

		for (int j = 0; j <= resolution; j++) {
			Vector2f offset(cos(delta * j), sin(delta * j));
			offset *= radius;

			Vector2f translated = center + matrices[i] * offset;
			glVertex2d(translated[0], translated[1]);

		}

		glEnd();
	}

}

void ParticleDrawer::dot(std::vector<Vector2f>& vertices, float point_size) {

	glEnable(GL_POINT_SMOOTH);
	glPointSize(point_size);

	glColor3f(1, 1, 1);

	glBegin(GL_POINTS);
	for (int i = 0; i<vertices.size(); i++) {
		Vector2f p = vertices[i];
		glVertex2fv(vertices[i].data);
	}
	glEnd();
}