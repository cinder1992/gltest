cmake_minimum_required(VERSION 2.8)
project(ogltest)

#make sure our cmake modules are found
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#Find the openGL and GLEW packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED) #needed to get the GLFW libraries
pkg_search_module(GLFW REQUIRED glfw3)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")
endif()

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
add_executable(ogltest loadShaders.cpp main.cpp)
target_link_libraries(ogltest ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARIES})
