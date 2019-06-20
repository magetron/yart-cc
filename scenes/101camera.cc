#include <iostream>
#include <cfloat>

#include "sphere.h"
#include "hittablelist.h"
#include "camera.h"

#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

vec3 colour (const ray& r, hittable *world, int depth) {
	hit_record rec;
	if (world -> hit(r, 0.001, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		if ( (depth < 50) && (rec.mat_ptr -> scatter(r, rec, attenuation, scattered))  ) 
				return attenuation * colour (scattered, world, depth + 1);
		else return vec3(0, 0, 0);
	} else {
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main () {
	freopen("101camera.ppm", "w", stdout);

	int nx = 2000;
	int ny = 1000;
	int ns = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	camera cam(90, double(nx) / double(ny));

	double R = cos(M_PI / 4);

	hittable *list[2];
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
	hittable *world = new hittable_list(list, 2);

	for (int j = ny - 1; j >= 0; j--) 
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			
			for (int s = 0; s < ns; s++) {
				double u = double(i + drand48()) / double(nx);
				double v = double(j + drand48()) / double(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += colour(r, world, 0);
			}

			col /= double(ns);
			col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

			int ir = int (255.99 * col[0]);
			int ig = int (255.99 * col[1]);
			int ib = int (255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	
	fclose(stdout);
	return 0;
}
