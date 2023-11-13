cmake_minimum_required(VERSION 3.23)

# set the project name
project(GraphicLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GL_ENABLE_OPENGL "Use OpenGL has a graphic library" ON)
option(GL_ENABLE_EXAMPLES "Build example projects" OFF)

add_subdirectory(Source)

if(GL_ENABLE_EXAMPLES)
	add_subdirectory(Examples)
endif()