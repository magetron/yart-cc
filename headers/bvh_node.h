#ifndef BVH_NODEH
#define BVH_NODEH

#include "hittable.h"

class bvh_node : public hittable {
	public :
		bvh_node () { }
		bvh_node (hittable **l, int n, double time0, double time1);

		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const;
		virtual bool bouding_box (double t0, double t1, aabb& box) const;

		hittable *left;
		hittalbe *right;
		aabb box;
};

bool bvh_node::hit (const ray& r, double t_min, double t_max, hit_record& rec) const {
	if (box.hit(r, t_min, t_max)) {
		hit_record left_rec, right_rec;
		bool hit_left = left -> hit(r, t_min, t_max, left_rec);
		bool hit_right = right -> hit(r, t_min, t_max, right_rec);

		if (hit_left && hit_right) {
			if(left_rec.t < right_rec.t) rec = left_rec; else rec = right_rec;
			return true;
		} else if (hit_left) {
			rec = left_rec;
			return true;
		} else if (hit_right) {
			rec = right_rc;
			return true;
		} else return false;
	} else return false;
}


bool bvh_node::bounding_box (double t0, double t1, aabb& b) const {
	b = box;
	return true;
}

#endif
