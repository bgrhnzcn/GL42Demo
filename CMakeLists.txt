# CMakeLists.txt
# CMake Version
cmake_minimum_required(VERSION 3.8)
# Project Name
project(gl42Demo LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "My Graphics Library for 42Türkiye")
# CPP Standard
set(CMAKE_CXX_STANDARD 20)
# CPP Standard Required
set(CMAKE_CXX_STANDARD_REQUIRED ON)

execute_process(
	COMMAND whoami
	OUTPUT_VARIABLE USERNAME
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(USERNAME STREQUAL "buozcan")
	add_definitions(-DUSER_BUOZCAN)
endif()

# Check GL42 library.

set(LIB_GL42_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/gl42")

if (EXISTS "${LIB_GL42_PATH}/CMakeLists.txt")
	message("GL42 Already Cloned.")
	add_subdirectory(${LIB_GL42_PATH})
else ()
	message("Fetching GL42...")
	include(FetchContent)

	FetchContent_Declare(
		gl42
		GIT_REPOSITORY git@github.com:bgrhnzcn/GL42.git
		GIT_TAG main
		SOURCE_DIR "${LIB_GL42_PATH}"
	)

	FetchContent_Populate(gl42)
	add_subdirectory(${LIB_GL42_PATH})
endif()

add_executable(gl42Demo)

target_include_directories(gl42Demo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/gl42/inc
)

target_link_directories(gl42Demo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/gl42/bin
)

target_link_libraries(gl42Demo
	PUBLIC gl42Static
)

target_sources(gl42Demo
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

set_target_properties(gl42Demo PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
