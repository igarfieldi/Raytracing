#pragma once

#include "material.hpp"
#include "rng.hpp"
#include "math.hpp"
#include <iostream>

namespace raytracer {

	template < class T >
	class lambertian : material<T> {
	private:
		vector_type m_albedo;
		static thread_local rng<T> rng;

	public:
		// Default is a black lambertian
		lambertian() : m_albedo(0) {}
		lambertian(const vector_type &albedo) : m_albedo(albedo) {}
		lambertian(const lambertian &) = default;
		lambertian(lambertian &&) = default;
		lambertian &operator=(const lambertian &) = default;
		lambertian &operator=(lambertian &&) = default;
		~lambertian() = default;

		std::pair<vector_type, vector_type> sample_brdf(const vector_type &wo, const vector_type &normal) const override {
			(void)wo;

			// Perform cosine-weighted sampling in hemisphere
			T r1 = rng.generate();
			T r2 = rng.generate();
			T r1s = std::sqrt(r1);
			T a = T(2) * pi<T> * r2;
			vector_type sample(
				std::cos(a) * r1s,
				std::sin(a) * r1s,
				std::sqrt(T(1) - r1)
			);

			// Transform the sample into world coordinates
			// TODO: Normal is up, but what about the other two?
			auto[tangent, bitangent] = create_base(normal);

			return {
				transform(sample, tangent, bitangent, normal),
				m_albedo * inv_pi<T>
			};
		}

		T pdf(const vector_type &wi, const vector_type &wo, const vector_type &normal) const override {
			(void)wo;

			return std::max(T(0), wi.dot(normal)) * inv_pi<T>;
		}
	};

	template < class T >
	thread_local rng<T> lambertian<T>::rng(T(0), T(1));

} // namespace raytracer