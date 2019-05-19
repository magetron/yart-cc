#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
	public:
		camera (vec3 look_from, vec3 look_at, vec3 vup, double vfov, double aspect) {
			vec3 u, v, w;
			double theta = vfov * M_PI / 180;
			double half_height = tan(theta / 2);
			double half_width = aspect * half_height;

			origin = look_from;
			w = unit_vector(look_from - look_at);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			lower_left_corner = vec3(-half_width, -half_height, -1.0);
			lower_left_corner = origin - half_width * u - half_height * v - w;
			horizontal = 2 * u * half_width;
			vertical = 2 * v * half_height;
		
		}

		ray get_ray (double u, double v) {
			return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		}

		vec3 origin;
		vec3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
};

#endif
