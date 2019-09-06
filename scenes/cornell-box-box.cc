#include <iostream>
#include <cfloat>
#include <thread>

#include "headers/hittable_list.h"
#include "headers/camera.h"

#include "headers/objects/sphere.h"
#include "headers/objects/xy_rect.h"
#include "headers/objects/xz_rect.h"
#include "headers/objects/yz_rect.h"
#include "headers/objects/flip_normals.h"
#include "headers/objects/box.h"

#include "headers/textures/constant_texture.h"
#include "headers/textures/noise_texture.h"

#include "headers/materials/diffuse_light.h"
#include "headers/materials/lambertian.h"

hittable *cornell_box () {
	hittable **list = new hittable*[8];
	int i = 0;
	material *red 	= new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));	
	material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
	material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
	material *light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));
	list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
	list[i++] = new box(vec3(130, 0, 65), vec3(295, 165, 230), white);
	list[i++] = new box(vec3(265, 0, 295), vec3(430, 330, 460), white);
	return new hittable_list(list, i);
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
	freopen("cornell-box-box.ppm", "w", stdout);

	int nx = 200;
	int ny = 200;
	int ns = 50;
	int max_thread = 8; // please note: max_thread shall always be a divisor of ny

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 look_from(278, 278, -800);
 	vec3 look_at(278, 278, 0);
	double dist = (look_from - look_at).length();
	double aperture = 0.0;
	double fov = 40.0;
	camera cam(look_from, look_at, vec3(0.0, 1.0, 0.0), fov, double(nx) / double(ny), aperture, dist, 0.0, 0.0);

	double R = cos(M_PI / 4);

	hittable *world = cornell_box();

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
