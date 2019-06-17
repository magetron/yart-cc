#ifndef PERLINH
#define PERLINH

#include "../swap.h"

inline double trilinear_interp (double c[2][2][2], double u, double v, double w) {
	double accum = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				accum += (i * u + (1 - i) * (1 - u)) * (j * v + (1 - j) * (1 - v)) *(k * w + (1 - k) * (1 - w)) * c[i][j][k];
	return accum;
}

class perlin {
	public :
		double noise (const vec3& p) const {
			double u = p.x() - floor(p.x());
			double v = p.y() - floor(p.y());
			double w = p.z() - floor(p.z());
			
			u = (u * u) * (3 - 2 * u);
			v = (v * v) * (3 - 2 * v);
			w = (w * w) * (3 - 2 * w);

			int i = floor(p.x());
			int j = floor(p.y());
			int k = floor(p.z());

			double c[2][2][2];

			for (int ii = 0; ii < 2; ii++)
				for (int jj = 0; jj < 2; jj++)
					for (int kk = 0; kk < 2; kk++)
						c[ii][jj][kk] = ranfloat[perm_x[(i + ii) & 255] ^ perm_y[(j + jj) & 255] ^ perm_z[(k + kk) & 255]];
				
			return trilinear_interp(c, u, v, w);
		}

		static double* 	ranfloat;
		static int*	perm_x;
		static int*	perm_y;
		static int* perm_z;
};

static double* perlin_generate () {
	double* p = new double[256]; 
	for (int i = 0; i < 256; i++) p[i] = drand48();
	return p;
}

void permute (int *p, int n) {
	for (int i = n - 1; i > 0; i--) {
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
