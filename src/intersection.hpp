#pragma once

#include "vec.hpp"

namespace raytracer {

	template < class T >
	class primitive;

	template < class T >
	struct intersection {
		using type = T;

		T distance;
		const primitive <T> *primitive;
	};

} // namespace raytracer