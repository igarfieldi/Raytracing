#pragma once

#include <array>
#include <assert.h>
#include <ostream>

namespace raytracer {

	template < class T, size_t D >
	class vector {
	public:
		using type = T;
		static constexpr size_t dimensions = D;
		static_assert(dimensions > 0, "Vector must have dimensionality of at least 1");

	private:
		std::array<type, dimensions> m_data;

		template < size_t Count, class T, class... Args >
		void expand(T val, Args... args) {
			static_assert(Count < dimensions, "Too many arguments to construct vector");
			m_data[Count] = val;
			expand<Count + 1>(std::forward<Args>(args)...);
		}

		template < size_t Count, class T >
		void expand(T val) {
			static_assert(Count < dimensions, "Too many arguments to construct vector");
			m_data[Count] = val;
		}

	public:
		vector() : m_data{ 0 } {}
		explicit vector(T val) : m_data{} {
			m_data.fill(val);
		}
		explicit vector(const std::array<type, dimensions> &vals) : m_data(vals) {}
		explicit vector(std::array<type, dimensions> &&vals) : m_data(std::move(vals)) {}

		template < class... Args, typename = std::enable_if_t<sizeof...(Args) >= 2 > >
		vector(Args... args) : m_data{} {
			expand<0>(std::forward<Args>(args)...);
		}

		vector(const vector &v) = default;
		vector(vector &&v) = default;
		vector &operator=(const vector &v) = default;
		vector &operator=(vector &&v) = default;
		~vector() = default;

		T &operator[](size_t index) {
			assert(index < dimensions);
			return m_data[index];
		}

		const T &operator[](size_t index) const {
			assert(index < dimensions);
			return m_data[index];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ <= 4> >
		T &x() {
			return m_data[0];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ <= 4> >
		const T &x() const {
			return m_data[0];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ >= 2 && D_ <= 4> >
		T &y() {
			return m_data[1];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ >= 2 && D_ <= 4> >
		const T &y() const {
			return m_data[1];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ >= 3 && D_ <= 4> >
		T &z() {
			return m_data[2];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ >= 3 && D_ <= 4> >
		const T &z() const {
			return m_data[2];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ == 4> >
		T &w() {
			return m_data[3];
		}

		template < size_t D_ = dimensions, typename = std::enable_if_t<D_ == 4> >
		const T &w() const {
			return m_data[3];
		}

		vector<type, dimensions> &operator+=(const vector<type, dimensions> &v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] += v.m_data[i];
			}
			return *this;
		}

		vector<type, dimensions> &operator+=(type v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] += v;
			}
			return *this;
		}

		vector<type, dimensions> &operator-=(const vector<type, dimensions> &v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] -= v.m_data[i];
			}
			return *this;
		}

		vector<type, dimensions> &operator-=(type v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] -= v;
			}
			return *this;
		}

		vector<type, dimensions> &operator*=(const vector<type, dimensions> &v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] *= v.m_data[i];
			}
			return *this;
		}

		vector<type, dimensions> &operator*=(type v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] *= v;
			}
			return *this;
		}

		vector<type, dimensions> &operator/=(const vector<type, dimensions> &v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] /= v.m_data[i];
			}
			return *this;
		}

		vector<type, dimensions> &operator/=(type v) {
			for (size_t i = 0; i < dimensions; ++i) {
				m_data[i] /= v;
			}
			return *this;
		}

		type dot(const vector<type, dimensions> &v) {
			T sum = 0;
			for (size_t i = 0; i < dimensions; ++i) {
				sum += m_data[i] * v.m_data[i];
			}
			return sum;
		}

		vector<type, dimensions> cross(const vector<type, dimensions> &v) {
			static_assert(dimensions == 3, "Cross product is only defined for vectors with 3 dimensions");
			return vector<type, dimensions>(
				y()*v.z() - z()*v.y(),
				z()*v.x() - x()*v.z(),
				x()*v.y() - y()*v.x()
			);
		}

		type length() const {
			return std::sqrt(this->dot(*this));
		}

		vector<type, dimensions> &normalize() {
			return (*this) *= T(1) / length();
		}
	};

	template < class T, size_t D >
	vector<T, D> operator+(vector<T, D> v1, const vector<T, D> &v2) {
		return v1 += v2;
	}

	template < class T, size_t D >
	vector<T, D> operator+(vector<T, D> v, T f) {
		return v += f;
	}

	template < class T, size_t D >
	vector<T, D> operator+(T f, vector<T, D> v) {
		return v += f;
	}

	template < class T, size_t D >
	vector<T, D> operator-(vector<T, D> v1, const vector<T, D> &v2) {
		return v1 -= v2;
	}

	template < class T, size_t D >
	vector<T, D> operator-(vector<T, D> v, T f) {
		return v -= f;
	}

	template < class T, size_t D >
	vector<T, D> operator-(T f, vector<T, D> v) {
		return (-v) += f;
	}

	template < class T, size_t D >
	vector<T, D> operator*(vector<T, D> v1, const vector<T, D> &v2) {
		return v1 *= v2;
	}

	template < class T, size_t D >
	vector<T, D> operator*(vector<T, D> v, T f) {
		return v *= f;
	}

	template < class T, size_t D >
	vector<T, D> operator*(T f, vector<T, D> v) {
		return v *= f;
	}

	template < class T, size_t D >
	vector<T, D> operator/(vector<T, D> v1, const vector<T, D> &v2) {
		return v1 /= v2;
	}

	template < class T, size_t D >
	vector<T, D> operator/(vector<T, D> v, T f) {
		return v /= f;
	}

	template < class T, size_t D >
	vector<T, D> operator/(T f, const vector<T, D> &v) {
		return vector<T, D>(f) / v;
	}

	template < class T, size_t D >
	T dot(const vector<T, D> &v1, const vector<T, D> &v2) {
		return v1.dot(v2);
	}

	template < class T, size_t D >
	vector<T, D> cross(const vector<T, D> &v1, const vector<T, D> &v2) {
		return v1.cross(v2);
	}

	template < class T, size_t D >
	T length(const vector<T, D> &v) {
		return v.length();
	}

	template < class T, size_t D >
	vector<T, D> normalize(vector<T, D> v) {
		return v.normalize();
	}

	template < class T, size_t D >
	std::ostream &operator<<(std::ostream &stream, const vector<T, D> &v) {
		stream << "( ";
		for (size_t i = 0; i < D; ++i) {
			stream << v[i] << ' ';
		}
		stream << ')';
		return stream;
	}

} // namespace raytracer