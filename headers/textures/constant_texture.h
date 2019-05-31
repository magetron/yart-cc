#ifndef CONSTANT_TEXTUREH
#define CONSTANT_TEXTUREH

#include "../texture.h"

class constant_texture : public texture {
	public :
		constant_texture () { }
		constant_texture (vec3 c) : colour(c) {  }
		
		virtual vec3 value (double u, double v, const vec3& p) const {
			return colour;
		}

		vec3 colour;
};

#endif
