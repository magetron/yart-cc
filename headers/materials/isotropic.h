#ifndef ISOTROPICH
#define ISOTROPICH

#include "../material.h"
#include "lambertian.h"

class isotropic : public material {
	public:
		isotropic (texture *a) : albedo(a) { }
		virtual bool scatter (const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scatterd) const {
			scatterd = ray(rec.p, random_in_unit_sphere());
			attenuation = albedo -> value(rec.u, rec.v, rec.p);
			return true;
		}
		texture *albedo;
};

#endif
