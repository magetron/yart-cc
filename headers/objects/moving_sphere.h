#ifndef MOVING_SPHEREH
#define MOVING_SPHEREH

#include "../hittable.h"
#include "../aabb.h"

class moving_sphere : public hittable {
	public :
		moving_sphere () { }
		moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, material *m) :
			centre0(cen0), centre1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) { };

		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const;
		virtual bool bounding_box (double t0, double t1, aabb& box) const;

		vec3 centre (double time) const;
		vec3 centre0, centre1;
		double time0, time1;
		double radius;
		material *mat_ptr;
};

vec3 moving_sphere::centre (double time) const {
	return centre0 + ((time - time0) / (time1 - time0)) * (centre1 - centre0);
}

bool moving_sphere::bounding_box (double t0, double t1, aabb& box) const {
	aabb box0(centre(t0) - vec3(radius, radius, radius), centre(t0) + vec3(radius, radius, radius));
	aabb box1(centre(t1) - vec3(radius, radius, radius), centre(t1) + vec3(radius, radius, radius));
	box = surrounding_box(box0, box1);
	return true;
}

bool moving_sphere::hit (const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - centre(r.time());
	double a = dot(r.direction(), r.direction());
	double b = dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double determinant = b * b - a * c;

	if (determinant > 0) {
		double tmp = (- b - sqrt(determinant)) / a;
		if ( (tmp < t_max) && (tmp > t_min) ) {
			rec.t = tmp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - centre(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		tmp = (-b + sqrt(determinant)) / a;
		if ( (tmp < t_max) && (tmp > t_min) ) {
			rec.t = tmp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - centre(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}	

#endif
