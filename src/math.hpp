#pragma once

#include "vec.hpp"
#include <tuple>

namespace raytracer {

	template < class T >
	inline constexpr T pi = T(3.1415926535897932384626433832795L);

	template < class T >
	inline constexpr T inv_pi = T(1)/pi<T>;

	template < class T >
	inline constexpr T epsilon = T(0.00000125);

	template < class T >
	T rad2deg(T val) {
		return val * T(180) * inv_pi<T>;
	}

	template < class T >
	T deg2rad(T val) {
		return pi<T> * val / T(180);
	}

	template < class T >
	std::pair<vector<T, 3>, vector<T, 3>> create_base(const vector<T, 3> &v1) {
		// Create a perpendicular vector; swap the coordinates based on the originall vector's orientation
		vector<T, 3> v2(v1.z(), T(0), -v1.x());
		if (std::abs(v1.x()) <= std::abs(v1.y())) {
			v2 = vector<T, 3>(T(0), -v1.z(), v1.y());
		}
		v2.normalize();
		// Third vector via cross product (will be normalized already if v1 and v2 are)
		vector<T, 3> v3 = v2.cross(v1);
		return { v2, v3 };
	}

	template < class T >
	vector<T, 3> transform(const vector<T, 3> &v, const vector<T, 3> &b1, const vector<T, 3> &b2, const vector<T, 3> &b3) {
		// Apply transformation matrix (by hand for now)
		return vector<T, 3>(
			b1.x()*v.x() + b2.x()*v.y() + b3.x()*v.z(),
			b1.y()*v.x() + b2.y()*v.y() + b3.y()*v.z(),
			b1.z()*v.x() + b2.z()*v.y() + b3.z()*v.z()
		);
	}

} // namespace raytracer