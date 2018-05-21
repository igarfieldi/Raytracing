cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(raytracing LANGUAGES CXX)

add_executable(raytracer
	src/main.cpp
	src/vec.hpp
	src/material.hpp
	src/primitive.hpp
	src/sphere.hpp
	src/scene.hpp
	src/camera.hpp
	src/ray.hpp
	src/intersection.hpp)
	
target_include_directories(raytracer PRIVATE src)
target_compile_features(raytracer PUBLIC cxx_std_17)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)