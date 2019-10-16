#pragma once

#include <math.h>

namespace ohs623 {
	template<typename T>
	struct Vec2Base {
		Vec2Base() : Vec2Base(0, 0) {}
		Vec2Base(T x, T y) : x(x), y(y) {}

		T Length() { return sqrt(x*x + y*y); }

		Vec2Base<T> operator+ (const Vec2Base<T>& other) { return Vec2Base(this->x + other.x, this->y + other.y); }
		Vec2Base<T> operator- (const Vec2Base<T>& other) { return Vec2Base(this->x - other.x, this->y - other.y); }

		T x, y;
	};


	using Vec2F = Vec2Base<float>;
	using Vec2D = Vec2Base<double>;
	
	using Vec2 = Vec2F;


	template<typename T>
	struct Vec3Base {
		Vec3Base() : Vec3Base(0, 0, 0) {}
		Vec3Base(T x, T y, T z) : x(x), y(y), z(z) {}

		T Length() { return sqrt(x*x + y*y + z*z); }

		Vec3Base<T> operator+ (const Vec3Base<T>& other) { return Vec3Base(this->x + other.x, this->y + other.y, this->z + other.z); }
		Vec3Base<T> operator- (const Vec3Base<T>& other) { return Vec3Base(this->x - other.x, this->y - other.y, this->z - other.z); }

		T x, y, z;
	};


	using Vec3F = Vec3Base<float>;
	using Vec3D = Vec3Base<double>;
	
	using Vec3 = Vec3F;

}

namespace std {
	inline std::string to_string(const ohs623::Vec3& value) {
		return "{" + to_string(value.x) + ", " + to_string(value.y) + ", " + to_string(value.z) + "}";
	}
}
