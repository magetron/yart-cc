#ifndef AABBH
#define AABBH

inline double dmin (double a, double b) { return a < b ? a : b; }
inline double dmax (double a, double b) { return a > b ? a : b; }

class aabb {
	public :
		aabb () { }
		aabb (const vec3&a, const vec3& b) { _min = a; _max = b; }

		vec3 min() const { return _min; }
		vec3 max() const { return _max; }

		bool hit (const ray& r, double tmin, double tmax) const {
			for (int i = 0; i < 3; i++) {
				double t0 = dmin( (_min[i] - r.origin()[i]) / r.direction()[i],
								  (_max[i] - r.origin()[i]) / r.direction()[i] );
				double t1 = dmax( (_min[i] - r.origin()[i]) / r.direction()[i],
								  (_max[i] - r.origin()[i]) / r.direction()[i] );

				tmin = dmax(t0, tmin);
				tmax = dmin(t1, tmax);

				if (tmax <= tmin) return false;
			}
			return true;
		}

		vec3 _min;
		vec3 _max;
};

aabb surrounding_box (aabb box0, aabb box1) {
	vec3 small( dmin(box0.min().x(), box1.min().x()),
				dmin(box0.min().y(), box1.min().y()),
				dmin(box0.min().z(), box1.min().z()) );
	vec3 big  ( dmax(box0.max().x(), box1.max().x()),
				dmax(box0.max().y(), box1.max().y()),
				dmax(box0.max().z(), box1.max().z()) );
	return aabb(small, big);
}

#endif
