set(target ingredients)

set(ingredients_SOURCES
        glutils.cpp
        objmesh.cpp
        glslprogram.cpp
        cookbookogl.h
        scene.h scene.cpp
        glad/src/glad.c trianglemesh.cpp trianglemesh.h aabb.h
        scenerunner.h
        texture.h texture.cpp
        utils.h
        plane.cpp plane.h
	SolarSystem.hpp Planet.hpp)

add_library(${target} STATIC ${ingredients_SOURCES})

target_include_directories(${target} PUBLIC glad/include)

target_link_libraries(${target} PUBLIC glm)

set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${target} PROPERTY CXX_STANDARD_REQUIRED ON)
