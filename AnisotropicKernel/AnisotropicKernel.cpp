#include "AnisotropicKernel.h"


using namespace SurfaceReconstruction;
using namespace std;

vector<Matrix2f> AnisotropicKernel::calc(const vector<Vector2f>& particles, vector<Vector2f>& new_pos) {

	int num_particles = particles.size();

	vector<Matrix2f> aniso_array(num_particles);

	for (int i = 0; i < num_particles; i++) {
		Vector2f pos = particles[i];

		// Vector2f* neighbors = nullptr;// kd_tree(particles[i]);
		// If possible, I want to change this to kd-tree
		vector<Vector2f> neighbors;
		for (int j = 0; j < num_particles; j++) {
			if (i == j) continue;
			float dist = (particles[i] - particles[j]).length();
			if (dist < search_radius) neighbors.push_back(particles[j]);
		}

		// Initialize Anisotoropic Matrix
		Matrix2f anisotropy(1, 0, 0, 1);

		if (neighbors.size() > 0) {

			Vector2f weighted_mean(0, 0);
			Vector2f weighted_pos(0, 0);
			float weight = 0;
			float weighting_function = 0;

			for (int n = 0; n <  neighbors.size(); n++) {
				float magnitude = (neighbors[n] - pos).length();

				weight = 1 - pow((magnitude / search_radius), 3);
				weighting_function += weight;
				weighted_pos += neighbors[n] * weight;
			}

			weighted_mean = weighted_pos / weighting_function;	// New particle position
			new_pos[i] = weighted_mean;

			Matrix2f covariance = Matrix2f::identity();

			for (int n = 0; n <  neighbors.size(); n++) {
				float magnitude = (neighbors[n] - pos).length();

				weight = 1 - pow((magnitude / search_radius), 3);

				Vector2f weighted_distance = neighbors[n] - weighted_mean;

				covariance += weighted_distance.outer_product(weighted_distance) * weight;
			}


			covariance /= weighting_function;

			Matrix2f r, v, vt;
			Vector2f diag;
			covariance.svd(&r, &diag, &v);
			vt = v.transpose();


			if (neighbors.size() > threshold) {
				diag[1] = max(diag[1], diag[0] / eigenvalues_ratio);
				diag *= scaling_factor;
			} else {
				diag.setData(1.0f, 1.0f);
			}

			Matrix2f rt = r.transpose();
			Matrix2f diagnotics(diag[0], 0.0f, 0.0f, diag[1]);

			diagnotics.print();

			anisotropy = r * diagnotics * rt * (1 / kernel_radius);
		}

		aniso_array[i] = anisotropy;
	}

	return aniso_array;
}