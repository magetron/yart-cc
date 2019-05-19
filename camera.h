#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
	public:
		camera (double vfov, double aspect) {
			double theta = vfov * M_PI / 180;
			double half_height = tan(theta / 2);
			double half_width = aspect * half_height;

			lower_left_corner = vec3(-half_width, -half_height, -1.0);
			horizontal = vec3(2 * half_width, 0.0, 0.0);
			vertical = vec3(0.0, 2 * half_height, 0.0);
			origin = vec3(0.0, 0.0, 0.0);
		
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
