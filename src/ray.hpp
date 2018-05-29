#pragma once

#include "vec.hpp"

namespace raytracer {

	template < class T >
	struct ray {
		using type = T;
		using vector_type = vector<T, 3>;

		vector_type origin;
		vector_type direction;

		static ray<T> look_at(const vector_type &point, const vector_type &origin = vector_type(T(0))) {
			return { origin, (point - origin).normalize() };
		}
	};

} // namespace raytracer