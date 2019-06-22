#ifndef SPHEREH
#define SPHEREH

#include "../hittable.h"

class sphere: public hittable {
	public:
		sphere () { }
		sphere (vec3 cen, double r, material *m) : centre(cen), radius(r), mat_ptr(m)	{ } ;
		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const;
		virtual bool bounding_box (double t0, double t1, aabb& box) const;
		vec3 centre;
		double radius;
		material *mat_ptr;
};

void get_sphere_uv (const vec3& p, double& u, double& v) {
	double phi = atan2(p.z(), p.x());
	double theta = asin(p.y());
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

bool sphere::hit (const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - centre;
	double a = dot(r.direction(), r.direction());
	double b = dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double determinant = b * b - a * c; 		// should be b ^ 2 - 4 ac, however redundant two's are eliminated in future calculations
	if (determinant > 0) {
		double tmp = (- b - sqrt(determinant)) / a;
		if ( (tmp < t_max) && (tmp > t_min) ) {
			rec.t = tmp;
			rec.p = r.point_at_parameter(rec.t);
			get_sphere_uv((rec.p - centre) / radius, rec.u, rec.v);
			rec.normal = (rec.p - centre) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		tmp = (- b + sqrt(determinant)) / a;
		if ( (tmp < t_max) && (tmp > t_min) ) {
			rec.t = tmp;
			rec.p = r.point_at_parameter(rec.t);
			get_sphere_uv((rec.p -centre) / radius, rec.u, rec.v);
			rec.normal = (rec.p - centre) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

bool sphere::bounding_box (double t0, double t1, aabb& box) const {
	box = aabb(centre - vec3(radius, radius, radius), centre + vec3(radius, radius, radius));
	return true;
}

#endif
