#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"
#include "aabb.h"

class material;

struct hit_record {
	double t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

class hittable {
	public:
		virtual bool hit (const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
		virtual bool bounding_box (double t0, double t1, aabb& box) const = 0;
};

aabb surrounding_box (aabb box0, aabb box1) {
	vec3 small ( fmin(box0.min().x(), box1.min().x()),
				 fmin(box0.min().y(), box1.min().y()),
				 fmin(box0.min().z(), box1.min().z()) );
	vec3 big (	 fmax(box0.max().x(), box1.max().x()),
				 fmax(box0.max().y(), box1.max().y()),
				 fmax(box0.max().z(), box1.max().z()) );

	return aabb(small, big);
}

#endif
