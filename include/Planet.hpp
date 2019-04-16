#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Planet {
  std::string name;
  float radius;
  GLuint nmrSlices, nmrStacks;
public:
  // Public Variables. These can be accessible publicly but it isn't supposed to be changed.
  std::vector<float> planetVertices, planetColor;
  std::vector<int> planetIndices;

  Planet(float, GLuint, GLuint);
  void calculateLocation();

};