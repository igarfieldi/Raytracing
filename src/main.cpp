#include "vec.hpp"
#include "sphere.hpp"
#include <iostream>

int main() {
	using namespace raytracer;

	vector<float, 3> v(1.f, 2.f, 3.f);
	std::cout << v << std::endl;
	std::cout << v.z() << std::endl;
	std::cout << v.dot(v) << std::endl;

	return 0;
}