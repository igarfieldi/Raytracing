#pragma once

#include "primitive.hpp"
#include "vec.hpp"
#include "ray.hpp"

namespace raytracer {

	template < class T >
	class plane : primitive<T> {
	private:
		vector_type m_pos, m_normal;

	public:
		// Default constructor creates a plane at origin 0 and upwards normal
		plane() : m_pos(), m_normal(0, 0, 1), m_r2() {}
		plane(const vector_type &pos, vector_type normal) : m_pos(pos), m_normal(normal.normalize()) {}
		plane(const plane &s) = default;
		plane(plane &&s) = default;
		plane &operator=(const plane &s) = default;
		plane &operator=(plane &&s) = default;
		~plane() = default;

		T intersect(const ray<T> &ray) const override {
			T denom = m_normal.dot(ray.direction);
			if (std::abs(denom) <= epsilon<T>) {
				return T(-1);
			} else {
				return (m_normal.dot(m_pos) - m_normal.dot(ray.origin)) / denom;
			}
		}

		vector_type normal(const vector_type &hitpoint) const override {
			(void)hitpoint;
			return m_normal;
		}
	};

} // namespace raytracer