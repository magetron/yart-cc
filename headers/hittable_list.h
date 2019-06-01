#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"

class hittable_list: public hittable {
	public :
		hittable_list () { }
		hittable_list (hittable **l, int n) {	list = l;	list_size = n; 	}
		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const;
		virtual bool bounding_box (double t0, double t1, aabb& box) const;
		hittable **list;
		int list_size;
};

bool hittable_list::hit (const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record tmp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
		if (list[i] -> hit(r, t_min, closest_so_far, tmp_rec)) {
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	return hit_anything;
}

bool hittable_list::bounding_box (double t0, double t1, aabb& box) const {
	if (list_size < 1) return false;
	aabb tmp_box;
	bool true1 = list[0] -> bounding_box(t0, t1, tmp_box);
	if (!true1) return false;
	else box = tmp_box;

	for (int i = 1; i < list_size; i++) 
		if (list[0] -> bounding_box(t0, t1, tmp_box)) box = surrounding_box(box, tmp_box);
		else return false;
	
	return true;
}

#endif



