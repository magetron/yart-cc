#ifndef MATERIALH
#define MATERIALH

#include "hittable.h"
#include "texture.h"

struct hit_record;

class material {
	public:
		virtual bool scatter (const ray& r_in, const hit_record& rec, vec3& attenuation, ray&scattered) const = 0;
		virtual vec3 emitted (double u, double v, const vec3& p) const {
			return vec3(0, 0, 0);
		}	
};

#endif
