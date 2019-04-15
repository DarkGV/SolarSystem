#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Planet.hpp"

class Render {
  std::vector<Planet*> Planets;
  GLuint positionHandle;
  void transferData();

public:
  GLuint positionArrayObject, facesElementBuffer, VertexArrayObject;
  Render();
  void draw();
};