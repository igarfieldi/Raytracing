#pragma once

#include "vec.hpp"
#include "intersection.hpp"
#include "ray.hpp"

namespace raytracer {

	template < class T >
	class primitive {
	public:
		using type = T;
		using vector_type = vector<T, 3>;

		intersection<T> intersect(const ray &) const = 0;
		vector_type normal(const vector_type &) const = 0;
	};

} // namespace raytracer