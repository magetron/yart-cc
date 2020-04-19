#include<iostream>

#include "headers/objects/sphere.h"

using namespace std;

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
	} while (dot(p, p) >= 1.0);
	return unit_vector(p);
}

inline double pdf(const vec3& p) {
	return 1 / (4 * M_PI);
}

int main () {
	int n = 1e6;
	double sum;
	for (int i = 0; i < n; i++) {
		vec3 d = random_in_unit_sphere();
		double cosine_squared = d.z() * d.z();
		sum += cosine_squared / pdf(d);
	}
	cout << "I = " << sum / n << "\n";
	return 0;
}
