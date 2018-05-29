#pragma once

#include "primitive.hpp"
#include "vec.hpp"
#include "ray.hpp"

namespace raytracer {

	template < class T >
	class sphere : primitive<T> {
	private:
		vector_type m_pos;
		type m_rad, m_r2;

	public:
		// Default constructor creates a sphere at origin with radius 0
		sphere() : m_pos(), m_rad(), m_r2() {}
		sphere(const vector_type &pos, type rad) : m_pos(pos), m_rad(rad), m_r2(rad*rad) {}
		sphere(const sphere &s) = default;
		sphere(sphere &&s) = default;
		sphere &operator=(const sphere &s) = default;
		sphere &operator=(sphere &&s) = default;
		~sphere() = default;

		T intersect(const ray<T> &ray) const override {
			auto l = m_pos - ray.origin;
			T s = l.dot(ray.direction);
			T l2 = l.dot(l);

			if ((s < 0) && (l2 >= m_r2)) {
				return T(-1);
			}

			T m2 = l2 - s * s;
			if (m2 > m_r2) {
				return T(-1);
			}

			T q = std::sqrt(m_r2 - m2);
			T t1 = s - q;
			T t2 = s + q;
			if ((t2 > 0) && (t2 < t1)) {
				return t2;
			}
			else {
				return t1;
			}
		}

		vector_type normal(const vector_type &hitpoint) const override {
			return (hitpoint - m_pos).normalize();
		}
	};

} // namespace raytracer