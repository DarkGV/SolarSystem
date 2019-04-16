#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "../Planet.cpp"

class Render {
  std::vector<Planet*> Planets;
  GLuint positionHandle;
  GLuint programID = -1;
  //void initPerspective(glm::mat4&);
  GLuint VertexArrayObject, ElementBufferObject, VertexBufferObject;

public:
  Render();
  void transferData(Planet*);
  void draw();
  //void loadShaders(char*, char*);
};