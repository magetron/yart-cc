#ifndef FLIP_NORMALH
#define FLIP_NORMALH

#include "../hittable.h"

class flip_normals : public hittable {
	public:
		flip_normals (hittable* p) : ptr(p) { }
		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const {
			if (ptr -> hit(r, tmin, tmax, rec)) {
				rec.normal = - rec.normal;
				return true;
			} else return false;
		}

		virtual bool bounding_box (double t0, double t1, aabb& box) const {
			return ptr -> bounding_box(t0, t1, box);
		}

		hittable *ptr;
};

#endif
