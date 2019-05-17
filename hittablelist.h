#include "hittable.h"

class hittable_list: public hittable {
	public :
		hittable_list () { }
		hittable_list (hittable **l, int n) {	list = 1;	list_size = n; 	}
		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const;
		hittable **list;
		int list_size;
}

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



