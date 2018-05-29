cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(raytracing LANGUAGES CXX)

add_executable(raytracer
	src/main.cpp
	src/vec.hpp
	src/scene.hpp
	src/camera.hpp
	src/ray.hpp
	src/intersection.hpp
	src/rng.hpp
	src/math.hpp
	src/object.hpp
	src/primitive.hpp
	src/primitives/plane.hpp
	src/primitives/sphere.hpp
	src/primitives/triangle.hpp
	src/material.hpp
	src/materials/lambertian.hpp
	src/materials/mirror.hpp
	src/tracer.hpp
	src/tracers/raytracer.hpp)
	
target_include_directories(raytracer PRIVATE src)
target_compile_features(raytracer PUBLIC cxx_std_17)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)