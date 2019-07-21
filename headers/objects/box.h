#ifndef BOXH
#define BOXH

#include "../hittable.h"

class box: public hittable {
	public:
		box () { }
		box (const vec3& p0, const vec3& p1, material *ptr);
		virtual bool hit (const ray& r, double t0, double t1, hit_record& rec) const;
		virtual bool bounding_box (double t0, double t1, aabb& box) const {
			box = aabb(pmin, pmax);
			return true;
		}
		
		vec3 pmin, pmax;
		hittable *list_ptr;
};


#endif
