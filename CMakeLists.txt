cmake_minimum_required(VERSION 3.5)

set(EXECUTABLE_OUTPUT_PATH ../bin)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "-O3 -Wall -DNDEBUG")
else()
	set(CMAKE_CXX_FLAGS "-O0 -DDEBUG")
endif()

project(vtn)

file(GLOB SRC "src/*.cpp")
include_directories(include)
add_executable(${PROJECT_NAME} ${SRC})
