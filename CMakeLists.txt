cmake_minimum_required(VERSION 3.16)
project(CMorgan C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default to Debug with single-configuration generators; IDE generators can
# select Debug from their configuration menu.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Build the library from C sources outside the tests and generated build files.
file(GLOB_RECURSE CMORGAN_LIBRARY_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)
list(FILTER CMORGAN_LIBRARY_SOURCES EXCLUDE REGEX "[/\\]tests[/\\]")
list(FILTER CMORGAN_LIBRARY_SOURCES EXCLUDE REGEX "[/\\](build|CMakeFiles)[/\\]")

if(CMORGAN_LIBRARY_SOURCES)
	add_library(cmorgan STATIC ${CMORGAN_LIBRARY_SOURCES})
	target_include_directories(cmorgan PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}"
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
	)
endif()

# tests/main.c is the entry point; compile the other test C files alongside it.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.c")
	file(GLOB CMORGAN_TEST_SOURCES CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c"
	)
	add_executable(cmorgan_test ${CMORGAN_TEST_SOURCES})
	target_include_directories(cmorgan_test PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}"
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/tests"
	)
	if(TARGET cmorgan)
		target_link_libraries(cmorgan_test PRIVATE cmorgan)
	endif()
endif()
