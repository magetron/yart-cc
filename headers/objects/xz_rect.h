#ifndef XZ_RECTH
#define XZ_RECTH

#include "../hittable.h"

class xz_rect : public hittable {
	public:
		xz_rect () { }
		xz_rect (double _x0, double _x1, double _z0, double _z1, double _k, material *mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) { };
		virtual bool hit (const ray& r, double t0, double t1, hit_record& rec) const;
		virtual bool bounding_box(double t0, double t1, aabb& box) const {
			box = aabb(vec3(x0, k - 0.0001, z0), vec3(x1, k + 0.0001, z1));
			return true;
		}
		
		material *mp;
		double x0, x1, z0, z1, k;
};

bool xz_rect::hit (const ray& r, double t0, double t1, hit_record& rec) const {
	double t = (k - r.origin().y()) / r.direction().y();
	if ((t < t0) || (t > t1)) return false;
	double x = r.origin().x() + t * r.direction().x();
	double z = r.origin().z() + t * r.direction().z();
	if ((x < x0) || (x > x1) || (z < z0) || (z > z1)) return false;
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal =  vec3(0, 1, 0);
	return true;
}

