#include "include/window.hpp"

Window::Window(GLfloat size, std::string title){
    this->width = this->height = size;
    this->title = title;
    if(!glfwInit()) throw "Error creating window " + title;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(this->window);
}

Window::Window(GLfloat width, GLfloat height, std::string title){
    this->width = width;
    this->height = height;
    this->title = title;
    if(!glfwInit()) throw "Error creating window " + title;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(this->window);
}

void Window::updateWindow(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldClose(){
    return glfwWindowShouldClose(window);
}