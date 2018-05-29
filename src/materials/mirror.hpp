#pragma once

#include "material.hpp"
#include "rng.hpp"

namespace raytracer {

	// TODO: put this somewhere else
	template < class T >
	constexpr T pi = T(3.1415926535897932384626433832795L);
	template < class T >
	constexpr T inv_pi = T(0.31830988618379067153776752674503L);

	template < class T >
	class mirror : material<T> {
	private:
		vector_type m_albedo;
		static thread_local rng<T> rng;

	public:
		// Default is a black lambertian
		mirror() : m_albedo(0) {}
		mirror(const vector_type &albedo) : m_albedo(albedo) {}
		mirror(const mirror &) = default;
		mirror(mirror &&) = default;
		mirror &operator=(const mirror &) = default;
		mirror &operator=(mirror &&) = default;
		~mirror() = default;

		std::pair<vector_type, vector_type> sample_brdf(const vector_type &wo, const vector_type &normal) const override {
			// No real sampling; specular reflections always return the same direction

			// Compute reflection vector; no need to normalize since it keeps the same length
			return {
				wo - T(2) * wo.dot(normal) * normal,
				m_color
			};
		}

		T pdf(const vector_type &wi, const vector_type &wo, const vector_type &normal) const override {
			(void)wi;
			(void)wo;
			(void)normal;

			// Since no sampling takes place, the probability is 1
			return T(1);
		}
	};

	template < class T >
	thread_local rng<T> mirror<T>::rng(T(0), T(1));

} // namespace raytracer