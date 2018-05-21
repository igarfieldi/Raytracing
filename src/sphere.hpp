#pragma once

#include "primitive.hpp"
#include "vec.hpp"
#include "ray.hpp"
#include "intersection.hpp"

namespace raytracer {

	template < class T >
	class sphere : primitive<T> {
	private:
		vector_type m_pos;
		type m_rad;

	public:
		// Default constructor creates a sphere at origin with radius 0
		sphere() : m_pos(), m_rad() {}
		sphere(const vector_type &pos, type rad) : m_pos(pos), m_rad(rad) {}
		sphere(const sphere &s) = default;
		sphere(sphere &&s) = default;
		sphere &operator=(const sphere &s) = default;
		sphere &operator=(sphere &&s) = default;
		~sphere() = default;

		intersection<T> intersect(const ray &ray) const {
			// TODO: proper test
			return { -1, this };
		}

		vector_type normal(const vector_type &hitpoint) const {
			return (hitpoint - m_pos).normalize();
		}

} // namespace raytracer