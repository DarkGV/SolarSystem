#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Window{
    GLfloat width, height;
    std::string title;
    GLFWwindow* window;
public:
    Window(GLfloat, std::string);
    Window(GLfloat, GLfloat, std::string);
    void updateWindow();
    bool shouldClose();
};