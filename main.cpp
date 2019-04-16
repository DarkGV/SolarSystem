#include <iostream>

#include "window.cpp"
#include "Render.cpp"

int main(){

  // Create on the heap memory
  Window* window = new Window(1024, "Sistema Solar");

  Render* render = new Render();

  Planet* p = new Planet(100.f, 36*5, 18*5);

  //render->loadShaders((char*)"shaders/vertex.glsl", (char*)"shaders/fragment.glsl");

  render->transferData(p);

  while(!window->shouldClose()){
    render->draw();
    window->updateWindow();
  }

  return 0;
}