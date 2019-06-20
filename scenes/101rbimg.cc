#include <iostream>

int main () {
	freopen("101rbimg.ppm", "w", stdout);
	
	int nx = 2000;
	int ny = 1000;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / float(nx);
			float g = 0.0;
			float b = float(j) / float(ny);
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	
	fclose(stdout);

	return 0;
}

