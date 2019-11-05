cmake_minimum_required(VERSION 3.15)
project(Ray_tracer)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs)

add_executable(Ray_tracer
        libs/Camera.h
        libs/Hitable.h
        libs/Hitablelist.h
        libs/Material.h
        libs/Ray.h
        libs/Sphere.h
        libs/Vec3.h
        example_img.cpp
        example_img2.cpp
        img3.cpp
        img4.cpp
        img5.cpp
        img6.cpp
        img7.cpp
        img8.cpp
        img9.cpp
        )
