#ifndef YZ_RECTH
#define YZ_RECTH

#include "../hittable.h"

class yz_rect : public hittable {
	public:
		yz_rect () { }
		yz_rect (double _y0, double _y1, double _z0, double _z1, double _k, material *mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) { };
		virtual bool hit (const ray&r, double t0, double t1, hit_record& rec) const;
		virtual bool bounding_box (double t0, double t1, aabb& box) const {
			box = aabb(vec3(k - 0.0001, y0, z0), vec3(k + 0.0001, y1, z1));
		}
		
		material *mp;
		double y0, y1, z0, z1, k;
};

bool yz_rect::hit (const ray& r, double t0, double t1, hit_record& rec) const {
	double t = (k - r.origin().x()) / r.direction().x();
	if ((t < t0) || (t > t1)) return false;
	double y = r.origin().y() + t * r.direction().y();
	double z = r.origin().z() + t * r.direction().z();
	if ((y < y0) || (y > y1) || (z < z0) || (z > z1)) return false;
	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(1, 0, 0);
	return true;
}

#endif 
