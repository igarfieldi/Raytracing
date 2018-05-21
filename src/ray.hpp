#pragma once

#include "vec.hpp"

namespace raytracer {

	template < class T >
	struct ray {
		using type = T;
		using vector_type = vector<T, 3>;

		vector_type origin;
		vector_type direction;
	};

} // namespace raytracer