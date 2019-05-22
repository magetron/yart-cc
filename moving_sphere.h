#ifndef MOVING_SPHEREH
#define MOVING_SPHEREH

class moving_sphere : public hittable {
	public :
		moving_sphere () { }
		moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, material *m) :
			centre0(cen0), centre1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) { };

		virtual bool hit (const ray& r, double tmin, double tmax, hit_record& rec) const;

		vec3 centre (double time) const;
		vec3 centre0, centre1;
		double time0, time1;
		double radius;
		material *mat_ptr;
};

vec3 moving_sphere::centre (double time) const {
	return centre0 + ((time - time0) / (time1 - time0)) * (centre1 - centre0);
}


#endif
