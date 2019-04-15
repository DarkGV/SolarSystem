#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.cpp"
#include "Render.cpp"

int main(){

  // Create on the heap memory
  Window* window = new Window(1024, "Sistema Solar");

  Render* render = new Render();

  while(!window->shouldClose()){
    render->draw();
    window->updateWindow();
  }

  return 0;
}