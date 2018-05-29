#pragma once

#include "intersection.hpp"
#include <tuple>

namespace raytracer {

	template < class T >
	class material {
	public:
		using type = T;
		using vector_type = vector<T, 3>;

		virtual ~material() {}

		virtual std::pair<vector_type, vector_type> sample_brdf(const vector_type &wo, const vector_type &normal) const = 0;
		virtual T pdf(const vector_type &wi, const vector_type &wo, const vector_type &normal) const = 0;
	};

} // namespace raytracer