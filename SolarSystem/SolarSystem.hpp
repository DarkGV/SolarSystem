#include "scene.h"
#include "glslprogram.h"

#include "Planet.hpp"

#include <glfw/glfw3.h>

#include <glm/glm.hpp>

#include "cookbookogl.h"


class SolarSystem : public Scene {
    GLSLProgram p;

    Planet* Sun, *Mercury, *Venus, *Earth, *Mars, *Jupiter, *Saturn,
    *Uranus, *Neptune;

    GLint width, height;
    glm::mat4 view, projection;

    void setMatrices(glm::mat4);
    void compileAndLinkShader(std::string, std::string);

public:
    SolarSystem();
    
    void initScene();
    void render();
    void resize(int, int);
    void update(float t);
};