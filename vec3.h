#include <cmath>
#include <cstdlib>
#include <iostream>

class vec3 {
	public:
		vec3() {}
		vec3(float e0, float e1, float e2) {
			e[0] = e0;
			e[1] = e1;
			e[2] = e2;
		}

		inline double x() const {	return e[0];	}
		inline double y() const {	return e[1]; 	}
		inline double z() const { 	return e[2];	}
		inline double r() const { 	return e[0];	}
		inline double g() const {	return e[1];	}
		inline double b() const {	return e[2];	}

		inline const vec3& operator + () const {	return *this;	}
		inline vec3 operator ~ () const {	return vec3(-e[0], -e[1], -e[2]); 	}
		inline float operator [] (int i) const {	return e[i];	}
		inline float& operator [] (int i) {	return e[i];	};

		inline vec3& operator += (const vec3 &v2);
		inline vec3& operator -= (const vec3 &v2);
		inline vec3& operator *= (const vec3 &v2);
		inline vec3& operator /= (const vec3 &v2);
		inline vec3& operator *= (const double t);
		inline vec3& operator /= (const double t);

		inline double length() const {
			return sqrt (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); 
		}

		inline double squared_length() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; 
		}

		inline void make_unit_vector();

		double e[3];
};

