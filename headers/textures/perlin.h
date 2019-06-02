#ifndef PERLINH
#define PERLINH

#include "../vec3.h"
#include "../swap.h"

class perlin {
	public :
		double noise (const vec3& p) const {
			double u = p.x() - floor(p.x());
			double v = p.y() - floor(p.y());
			double w = p.z() - floor(p.z());

			int i = int(4 * p.x()) & 255;
			int j = int(4 * p.y()) & 255;
			int k = int(4 * p.z()) & 255;
			
			return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
		}

		static float* 	ranfloat;
		static int*	perm_x;
		static int*	perm_y;
		static int* perm_z;
};

static float* perlin_generate () {
	double* p = new float[256]; 
	for (int i = 0; i < 256; i++) p[i] = drand48();
	return p;
}

void permute (int *p, int n) {
	for (int i = n - 1; i > 0 i--) {
		int target = int(drand48() * (i + 1));
		swap(p[i], p[target]);
	}
}

static int* perlin_generate_perm () {
	int* p = new int[256];
	for (int i = 0; i < 256; i++) p[i] = i;
	permute(p, 256);
	return p;
}

double* perlin::ranfloat = perlin_generate();
int* perlin::perm_x = perlin_generate_perm();
int* perlin::perm_y = perlin_generate_perm();
int* perlin::perm_z = perlin_generate_perm();

#endif
