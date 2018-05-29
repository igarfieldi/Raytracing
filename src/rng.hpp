#pragma once
#include <algorithm>
#include <functional>
#include <iterator>
#include <random>

namespace raytracer {

	template < class T, size_t S = T::state_size >
	T create_seeded_rng() {
		typename T::result_type seeds[S];
		std::random_device seeder;
		std::generate(std::begin(seeds), std::end(seeds), std::ref(seeder));
		std::seed_seq seq(std::begin(seeds), std::end(seeds));
		return T(seq);
	}

	template < class T, class D = std::uniform_real_distribution<T>, class E = std::mt19937 >
	class rng {
	public:
		using result_type = T;
		using engine_type = E;
		using distribution_type = D;

	private:
		engine_type m_engine;
		distribution_type m_dist;

	public:
		rng() : m_engine(create_seeded_rng<engine_type>()), m_dist() {
		}
		
		template < class... Args >
		rng(Args... args) : m_engine(create_seeded_rng<engine_type>()), m_dist(std::forward<Args>(args)...) {
		}

		rng(const rng&) = delete;
		rng(rng &&r) : m_engine(r.m_engine) {
		}

		rng &operator=(const rng&) = delete;
		rng &operator=(rng &&r) {
			m_engine = std::move(r.m_engine);
			return *this;
		}

		result_type generate() {
			return m_dist(m_engine);
		}

		std::vector<result_type> generate_sequence(size_t n) {
			std::vector<result_type> series;
			for (size_t i = 0; i < n; ++i) {
				series.push_back(m_dist(m_engine));
			}
			return series;
		}

		std::vector<result_type> &generate_sequence(size_t n, std::vector<result_type> &series) {
			series.reserve(series.size() + n);
			for (size_t i = 0; i < n; ++i) {
				series.push_back(m_dist(m_engine));
			}
			return series;
		}

		template < size_t N >
		std::array<result_type, N> generate_sequence() {
			std::array<result_type, N> series;
			for (size_t i = 0; i < N; ++i) {
				series[i] = m_dist(m_engine);
			}
			return series;
		}

		template < size_t N >
		std::array<result_type, N> &generate_sequence(std::array<result_type, N> &series) {
			for (size_t i = 0; i < n; ++i) {
				series[i] = m_dist(m_engine);
			}
			return series;
		}
	};

} // namespace cpputils