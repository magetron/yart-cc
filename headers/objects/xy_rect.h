#ifndef XY_RECTH
#define XY_RECTH

#include "../hittable.h"

class xy_rect : public hittable {
	public:
		xy_rect () { }
		xy_rect (double _x0, double _x1, double _y0, double _y1, double _k, material *mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) { };
		virtual bool hit (const ray& r, double t0, double t1, hit_record& rec) const;
		
		virtual bool bounding_box (double t0, double t1, aabb& box) const {
			box = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
			return true;
		}
		
		material* mp;
		double x0, x1, y0, y1, k;
};

bool xy_rect::hit (const ray& r, double t0, double t1, hit_record& rec) const {
	double t = (k - r.origin().z()) / r.direction().z();
	if ((t < t0) || (t > t1)) return false;
	double x = r.origin().x() + t * r.direction().x();
	double y = r.origin().y() + t * r.direction().y();
	if ((x < x0) || (x > x1) || (y < y0) || (y > y1)) return false;
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(0, 0, 1);
	return true;
}

#endif
