cmake_minimum_required (VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)

project (SOLARSYSTEM)

if(MSVC)
  add_definitions(/DNOMINMAX)
endif()

find_package( glm CONFIG REQUIRED )
find_package( glfw3 CONFIG REQUIRED )
find_package( OpenGL REQUIRED )

include_directories( include )

add_subdirectory( include )
add_subdirectory( SolarSystem )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
