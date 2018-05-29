#pragma once

#include "primitive.hpp"
#include "material.hpp"
#include <memory>

namespace raytracer {

	template < class T >
	class object {
	private:
		std::unqiue_ptr<primitive> m_prim;
		std::shared_ptr<material> m_mat;

	public:

		const primitive &primitive() const {
			return m_primitive;
		}

		const primitive &primitive() const {
			return m_primitive;
		}
	};

} // namespace raytracer