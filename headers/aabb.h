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

				if (tmax <= tmin) return flase;
			}
			return true;
		}

		vec3 _min;
		vec3 _max;
};

inline bool aabb::hit (const ray&r , double tmin, double tmax) const {
	for (int i =0; i < 3; i++) {
		double invD = 1.0 / r.direction()[i];
		double t0 = (min()[i] - r.origin()[i]) * invD;
		double t1 = (max()[i] - r.origin()[i]) * invD;

		if (invD < 0.0) std::swap(t0, t1);

		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;
		
		if (tmax <= tmin) return false;
	}
	return true;
}
