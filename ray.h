#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray {
	public:
		ray () { }
		ray (const vec3& a, const vec3& b, double ti = 0.0) {
			A = a;
			B = b;
			_time = ti;
		}
		
		vec3 origin() const 	{	return A; }
		vec3 direction() const 	{	return B; }
		double time() const 	{	return _time; }

		vec3 point_at_parameter (double t) const {	return A + t * B; }

		vec3 A;
		vec3 B;
		double _time;
};

#endif
