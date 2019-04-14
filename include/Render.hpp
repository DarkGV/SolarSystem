#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Planet.hpp"

class Render {
  std::vector<glm::vec3> PlanetsPositions;
  GLuint positionHandle;
  void transferData();

public:
  GLuint positionArrayObject, facesElementBuffer;
  Render();
  void draw();
};