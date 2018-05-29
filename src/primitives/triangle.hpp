#pragma once

#include "primitive.hpp"
#include "vec.hpp"
#include "ray.hpp"
#include <array>

namespace raytracer {

	template < class T >
	class triangle : primitive<T> {
	private:
		std::array<vector_type, 3> m_points;
		std::array<vector_type, 3> m_normals;

	public:
		// Default constructor creates a triangle with all points at origin 0 and all normals facing upwards
		// TODO: normalize them or what?
		triangle() : m_pos{ vector_type(0), vector_type(0), vector_type(0) }, 
			m_normals{ vector_type(0, 0, 1), vector_type(0, 0, 1), vector_type(0, 0, 1) } {}
		triangle(const std::array<vector_type, 3> &points, const vector_type &normal) : m_points(points), m_normals{ normal, normal, normal } {}
		triangle(const vector_type &p1, const vector_type &p2, const vector_type &p3,
			const vector_type &normal) : m_points{ p1, p2, p3 }, m_normals{ normal, normal, normal } {}
		triangle(const std::array<vector_type, 3> &points, const std::array<vector_type, 3> &normals) : m_points(points), m_normals(normals) {}
		triangle(const vector_type &p1, const vector_type &p2, const vector_type &p3,
			const std::array<vector_type, 3> &normals) : m_points{ p1, p2, p3 }, m_normals(normals) {}
		triangle(const std::array<vector_type, 3> &points,
			const vector_type &n1, const vector_type &n2, const vector_type &n3) : m_points(points), m_normals{ n1, n2, n3 } {}
		triangle(const vector_type &p1, const vector_type &p2, const vector_type &p3,
			const vector_type &n1, const vector_type &n2, const vector_type &n3) : m_points{ p1, p2, p3 }, m_normals{ n1, n2, n3 } {}
		triangle(const triangle &s) = default;
		triangle(triangle &&s) = default;
		triangle &operator=(const triangle &s) = default;
		triangle &operator=(triangle &&s) = default;
		~triangle() = default;

		T intersect(const ray<T> &ray) const override {
			// Vectors from point 1 to the other points
			auto e1 = m_points[1] - m_points[0];
			auto e2 = m_points[2] - m_points[0];

			auto h = ray.direction.cross(e2);
			T a = e1.dot(h);
			if (std::abs(a) <= epsilon<T>) {
				// Ray is parallel to triangle
				return T(-1);
			}
			T f = T(1) / a;

			// Barycentric coordinate no. 1
			auto s = ray.origin - m_points[0];
			T u = f * s.dot(h);
			if ((u < T(0)) || (u > T(1))) {
				return T(-1);
			}

			// Barycentric coordinate no. 1
			auto q = s.cross(e1);
			double v = f * ray.direction.dot(q);
			if ((v < T(0)) || (u + v > T(1))) {
				return T(-1);
			}

			return f * e2.dot(q);
		}

		vector_type normal(const vector_type &hitpoint) const override {
			// Three vectors from point 1 to the others
			auto v0 = m_points[1] - m_points[0];
			auto v1 = m_points[2] - m_points[0];
			auto v2 = hitpoint - m_points[0];
			// Solve linear equation system to find barycentric coordinates
			T d00 = v0.dot(v0);
			T d01 = v0.dot(v1);
			T d11 = v1.dot(v1);
			T d20 = v2.dot(v0);
			T d21 = v2.dot(v1);
			T denom = (d00 * d11 - d01 * d01);
			if (std::abs(denom) <= epsilon<T>) {
				// This should NOT happen!
				assert(false);
				return vector_type();
			} else {
				denom = T(1) / denom;
				T v = (d11 * d20 - d01 * d21) * denom;
				T w = (d00 * d21 - d01 * d20) * denom;
				// TODO: is normalization necessary?
				return ((T(1) - v - w) * m_normals[0] + v * m_normals[1] + w * m_normals[2]).normalize();
			}
		}
	};

} // namespace raytracer