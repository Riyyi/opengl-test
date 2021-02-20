# User config between these lines
# ------------------------------------------

# Set project name
set(NAME "final")

# ------------------------------------------

cmake_minimum_required(VERSION 3.1)

# Check if the build should include debugging symbols
option(DEBUG "" ON)
if(NOT DEBUG)
	# cmake -DDEBUG=off .. && make
	message("--- Release ---")
	set(CMAKE_BUILD_TYPE "Release")

	# -O3     = Optimizations that increase compilation time and performance
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
else()
	# cmake -DDEBUG=on .. && make
	message("--- Debug ---")
	set(CMAKE_BUILD_TYPE "Debug")

	# -Og     = Optimizations that do not interfere with debugging
	# -Wall   = All warnings about contructions that are easily avoidable
	# -Wextra = Extra warning flags not covered by -Wall
	# -pg     = Generate profile information for analysis with gprof
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall -Wextra -pg")
	# gprof final gmon.out > profile-data.txt
endif()

project(${NAME})
set(CMAKE_CXX_STANDARD 14)

# Include all headers
include_directories(
	"deps/glfw/include"
	"deps/glad/include"
	"deps/glm"
	"deps/stb"
	"deps/freetype/include"
	"include"
)

# Add source files
file(GLOB_RECURSE GLAD "deps/glad/*.c")
file(GLOB_RECURSE SOURCE "src/*.cpp")
set(SOURCES ${GLAD} ${SOURCE})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW target to project
add_subdirectory(deps/glfw)

# Add FreeType target to project
add_subdirectory(deps/freetype)

add_executable(${NAME} ${SOURCES})
target_link_libraries(${NAME} glfw freetype)
