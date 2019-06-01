#include "scene.h"
#include "glslprogram.h"

#include "Planet.hpp"

#include <glfw/glfw3.h>

#include <glm/glm.hpp>

#include "cookbookogl.h"
#include "Camera.hpp"
#include <unistd.h>


class SolarSystem : public Scene {
    GLSLProgram p;

    bool paused = true;

    Planet *Sun, *Mercury, *Venus, *Earth, *Mars, *Jupiter, *Saturn,
    *Uranus, *Neptune;

    GLint width, height;
    GLfloat camPosX, camPosY, camPosZ, camLookX, camLookY, camLookZ;
    Camera *c = new Camera(150.f, 30.f, -150.f, 0.f, 0.f, 0.f);
    glm::mat4 view, projection;

    void setMatrices(glm::mat4);
    void compileAndLinkShader(std::string, std::string);

public:
    SolarSystem();

    void keycallback(GLFWwindow*, int, int, int, int);
    void mousecallback(GLFWwindow*, double, double);
    void initScene();
    void render();
    void resize(int, int);
    void update(float t);
};
