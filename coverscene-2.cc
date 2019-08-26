#include <iostream>
#include <cfloat>
#include <thread>

#include "headers/hittable_list.h"
#include "headers/camera.h"
#include "headers/bvh_node.h"

#include "headers/objects/sphere.h"
#include "headers/objects/moving_sphere.h"
#include "headers/objects/xy_rect.h"
#include "headers/objects/xz_rect.h"
#include "headers/objects/yz_rect.h"
#include "headers/objects/flip_normals.h"
#include "headers/objects/box.h"
#include "headers/objects/translate.h"
#include "headers/objects/rotate_y.h"
#include "headers/objects/constant_medium.h"

#include "headers/textures/constant_texture.h"
#include "headers/textures/noise_texture.h"
#include "headers/textures/image_texture.h"

#include "headers/materials/diffuse_light.h"
#include "headers/materials/dielectric.h"
#include "headers/materials/lambertian.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

hittable *coverscene_2 () {
	int nb = 20;
	hittable **list = new hittable*[30];
	hittable **boxlist = new hittable*[10000];
	hittable **boxlist2 = new hittable*[10000];
	material *white = new lambertian(new constant_texture(vec3(0.75, 0.75, 0.75)));
	material *ground = new lambertian(new constant_texture(vec3(0.48, 0.83, 0.53)));
	int b = 0;
	for (int i = 0; i < nb; i++) 
		for (int j = 0; j < nb; j++) {
			double w = 100;
			double x0 = -1000 + i * w;
			double y0 = 0;
			double z0 = -1000 + j * w;
			double x1 = x0 + w;
			double y1 = 100 * (drand48() + 0.01);
			double z1 = z0 + w;
			boxlist[b++] = new box(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
		}
	int l = 0;
	list[l++] = new bvh_node(boxlist, b, 0, 1);
	material *light = new diffuse_light(new constant_texture(vec3(7, 7, 7)));
	list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
	vec3 centre(400, 400, 200);
	list[l++] = new moving_sphere(centre, centre + vec3(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
	list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(11.5));
	hittable *boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
	list[l++] = boundary;
	list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec3(0.2, 0.4, 0.9)));
	boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
	list[l++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1.0, 1.0, 1.0)));
	int nx, ny, nn;
	unsigned char *earth_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
	material *earth_mat = new lambertian(new image_texture(earth_data, nx, ny));
	list[l++] = new sphere(vec3(400, 200, 400), 100, earth_mat);
	texture *noitext = new noise_texture(0.1);
	list[l++] = new sphere(vec3(220, 280, 300), 80, new lambertian(noitext));
	int ns = 1000;
	for (int j = 0; j < ns; j++) 
		boxlist2[j] = new sphere(vec3(165 * drand48(), 165 * drand48(), 165 * drand48()), 10, white);
	list[l++] = new translate(new rotate_y(new bvh_node(boxlist2, ns, 0.0, 1.0), 15), vec3(-100, 270, 395));
	return new hittable_list(list, l);
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
	freopen("coverscene-2.ppm", "w", stdout);

	int nx = 1000;
	int ny = 1000;
	int ns = 1500;
	int max_thread = 8; // please note: max_thread shall always be a divisor of ny

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 look_from(278, 278, -800);
 	vec3 look_at(278, 278, 0);
	//double dist = (look_from - look_at).length();
	double dist = 10.0;
	double aperture = 0.0;
	double fov = 40.0;
	camera cam(look_from, look_at, vec3(0.0, 1.0, 0.0), fov, double(nx) / double(ny), aperture, dist, 0.0, 1.0);

	double R = cos(M_PI / 4);

	hittable *world = coverscene_2();

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
