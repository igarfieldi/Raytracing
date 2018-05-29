#include "vec.hpp"
#include "primitives/plane.hpp"
#include "primitives/triangle.hpp"
#include "primitives/sphere.hpp"
#include "materials/lambertian.hpp"
#include <iostream>

int main() {
	using namespace raytracer;

	vector<float, 3> v(1.f, 2.f, 3.f);
	std::cout << v << std::endl;
	std::cout << v.z() << std::endl;
	std::cout << v.dot(v) << std::endl;

	auto r = ray<float>::look_at(vec3f(20.f, 300.f, 20.f));
	plane<float> p(vec3f(0.f, 300.f, 0.f), vec3f(0.f, -1.f, 0.f));
	triangle<float> t(vec3f(-50.f, 300.f, -50.f), vec3f(-50.f, 300.f, 50.f), vec3f(50.f, 300.f, 50.f),
		vec3f(0.f, -1.f, 0.f));
	sphere<float> s(vec3f(0.f, 300.f, 0.f), 50.f);

	lambertian<float> l(vec3f(1.f, 1.f, 1.f));

	std::cout << p.intersect(r) << std::endl;
	std::cout << s.intersect(r) << std::endl;
	std::cout << t.intersect(r) << std::endl;
	auto[wi, brdf] = l.sample_brdf(r.direction, s.normal(r.origin + s.intersect(r) * r.direction));
	std::cout << wi << brdf << " " << std::endl;

	return 0;
}