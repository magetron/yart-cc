#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

vec3 random_in_unit_disk () {
	vec3 p;
	do {
		p = 2.0 * vec3(drand48(), drand48(), 0.0) - vec3(1.0, 1.0, 0.0);
	} while (dot(p, p) >= 1.0);
	return p;
}


class camera {
	public:
		camera (vec3 look_from, vec3 look_at, vec3 vup, double vfov, double aspect, double aperture, double focus_dist) {
			lens_radius = aperture / 2;
			double theta = vfov * M_PI/ 180;
			double half_height = tan(theta / 2);
			double half_width = aspect * half_height;

			origin = look_from;
			w = unit_vector(look_from - look_at);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			lower_left_corner = origin - half_width * u * focus_dist - half_height * v * focus_dist - focus_dist * w;
			horizontal = 2 * u * half_width * focus_dist;
			vertical = 2 * v * half_height * focus_dist;
		
		}

		ray get_ray (double s, double t) {
			vec3 rd = lens_radius * random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();
			return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}

		vec3 origin;
		vec3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		double lens_radius;
};

#endif
