#include <iostream>
#include <cfloat>
#include <thread>

#include "headers/hittable_list.h"
#include "headers/camera.h"

#include "headers/objects/sphere.h"
#include "headers/objects/xy_rect.h"
#include "headers/textures/constant_texture.h"
#include "headers/textures/noise_texture.h"
#include "headers/materials/diffuse_light.h"
#include "headers/materials/lambertian.h"

hittable *simple_light () {
	texture *noitext = new noise_texture(4);
	hittable **list = new hittable*[4];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(noitext));
	list[1] = new sphere(vec3(0, 1, 0), 1, new lambertian(noitext));
	list[2] = new sphere(vec3(0, 7 ,0), 2, new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	list[3] = new xy_rect(3, 5, 1, 3, -2, new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	return new hittable_list(list, 4);
}


vec3 colour (const ray& r, hittable *world, int depth) {
	hit_record rec;
	if (world -> hit(r, 0.001, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		vec3 emitted = rec.mat_ptr -> emitted(rec.u, rec.v, rec.p);
		if ( (depth < 50) && (rec.mat_ptr -> scatter(r, rec, attenuation, scattered))  ) 
				return emitted + attenuation * colour (scattered, world, depth + 1);
		else return emitted;
	} else return vec3(0, 0, 0);
}

void renderer (int nx, int ny, int ns, int j_max, int j_min, int i_min, int i_max, camera cam, hittable *world, int ***output_img) {
	for (int j = j_max; j >= j_min; j--) {
		output_img[j] = new int* [i_max - i_min + 1];
		for (int i = i_min; i <= i_max; i++) {
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

			output_img[j][i] = new int [3];
			output_img[j][i][0] = ir;
			output_img[j][i][1] = ig;
			output_img[j][i][2] = ib;
		}
	}
}	


int main () {
	freopen("diffuse-light.ppm", "w", stdout);

	int nx = 2000;
	int ny = 1000;
	int ns = 500;
	int max_thread = 8; // please note: max_thread shall always be a divisor of ny

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 look_from(13, 2, 3);
 	vec3 look_at(0, 0, 0);
	double dist = (look_from - look_at).length();
	double aperture = 0.0;
	camera cam(look_from, look_at, vec3(0.0, 1.0, 0.0), 20, double(nx) / double(ny), aperture, dist, 0.0, 0.0);

	double R = cos(M_PI / 4);

	hittable *world = simple_light();

	int ***output_img = new int** [ny];
	
	int thread_interval = ny / max_thread;
	std::thread threads[max_thread];
	int thread_counter = 0;
	for (int i = 0; i < max_thread; i++) 
		threads[i] = std::thread(renderer, nx, ny, ns, (i + 1) * thread_interval - 1, i * thread_interval, 0, nx - 1, cam, world, output_img);

	for (int i = 0; i < max_thread; i++) threads[i].join();

	for (int j = ny - 1; j >= 0; j--) 
		for (int i = 0; i < nx; i++) 
			std::cout << output_img[j][i][0] << " " << output_img[j][i][1] << " " << output_img[j][i][2] << std::endl;

	fclose(stdout);
	return 0;
}
