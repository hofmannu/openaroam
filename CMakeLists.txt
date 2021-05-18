cmake_minimum_required(VERSION 3.12)

project(openaroam 	VERSION 1.0
	DESCRIPTION "Open source implementation in C++ of the microscope"
	LANGUAGES CXX)


add_subdirectory(src/)
add_subdirectory(lib/)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(OpenGL_GL_PREFERENCE GLVND)
cmake_policy(SET CMP0079 NEW)

add_executable(main_exp src/main.cpp)
target_link_libraries(main_exp PUBLIC Interface)