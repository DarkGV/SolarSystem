#include "scene.h"
#include "glslprogram.h"

#include "Planet.hpp"

#include <glm/glm.hpp>

#include "cookbookogl.h"


class SolarSystem : public Scene {
    GLSLProgram p;

    Planet* Sun, *Mercury, *Venus, *Earth, *Mars, *Jupiter, *Saturn,
    *Uranus, *Neptune;

    GLint width, height;
    glm::mat4 model, view, projection;

    void setMatrices();
    void compileAndLinkShader(std::string, std::string);

public:
    SolarSystem();

    void renderMercury();
    void initScene();
    void render();
    void resize(int, int);
    void update(float t);
};