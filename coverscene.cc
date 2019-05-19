#include <iostream>
#include <cfloat>

#include "sphere.h"
#include "hittablelist.h"
#include "camera.h"

#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"


hittable *random_sphere_scene () {
	int n = 500;
	hittable **list = new hittable* [n + 1];
	list [0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
		for (int b = -11; b < 11; b++) {
			double c_mat = drand48();
			vec3 centre(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
			if ( (centre - vec3(4.0, 0.2, 0.0)).length() > 0.9 ) {
				if (c_mat < 0.8) 		list[i ++] = new sphere(centre, 0.2, new lambertian(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
				else if (c_mat < 0.95) 	list[i ++] = new sphere(centre, 0.2, new metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
				else					list[i ++] = new sphere(centre, 0.2, new dielectric(1.5));

			}
		}
	
	list[i ++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i ++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i ++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hittable_list(list, i);
}


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
	freopen("coverscene.ppm", "w", stdout);

	int nx = 2000;
	int ny = 1000;
	int ns = 10;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 look_from(13, 2, 3);
	vec3 look_at(0, 0, 0);
	double dist = (look_from - look_at).length();
	double aperture = 0.25;
	camera cam(look_from, look_at, vec3(0.0, 1.0, 0.0), 20, double(nx) / double(ny), aperture, dist);

	double R = cos(M_PI / 4);

	hittable *world = random_sphere_scene();

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
