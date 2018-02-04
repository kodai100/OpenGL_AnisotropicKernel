#pragma once

#define WIN_X 1280
#define WIN_Y 720

const int num_particles = 4096;

const float search_radius = 0.3f;
const float kernel_radius = 0.08f;
const int threshold = 4;
const float scaling_factor = 0.9f;	// ks
const float eigenvalues_ratio = 2;	// kr