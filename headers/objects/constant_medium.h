#ifndef CONSTANT_MEDIUMH
#define CONSTANT_MEDIUMH

#include "../hittable.h"

class constant_medium : public hittable {
	public :
		constant_medium (hittable *b, double d, texture *a) : boundary(b), density(d) {
			phase_function = new isotropic(a); 
		}

		virtual bool hit (const ray& r, double t_min, double t_max, hit_record& rec) const;
		virtual bool bounding_box (double t0, double t1, aabb& box) const {
			return boundary -> bounding_box(t0, t1, box);
		}
		hittable *boundary;
		double density;
		material *phase_function;
};

bool constant_medium::hit (const ray&r, double t_min, double t_max, hit_record& rec) const {
	bool db = (drand48() < 0.000001);
	db = false;
	hit_record rec1, rec2;
	if (boundary -> hit(r, -FLT_MAX, FLT_MAX, rec1)) {
	
	}
	return false;
}


#endif
