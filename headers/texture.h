#ifndef TEXTUREH
#define TEXTUREH

class texture {
	public :
		virtual vec3 value (double u, double v, const vec3& p) const = 0;
};

#endif
