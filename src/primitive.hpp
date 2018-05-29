#pragma once

#include "vec.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "math.hpp"

namespace raytracer {

	template < class T >
	class primitive {
	public:
		using type = T;
		using vector_type = vector<T, 3>;

		virtual ~primitive() {}

		virtual T intersect(const ray<T> &) const = 0;
		virtual vector_type normal(const vector_type &) const = 0;
	};

} // namespace raytracer