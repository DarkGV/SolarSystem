#include <iostream>
#include <string>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Icosahedron {
  const float X = 0.525731112119133606f;
  const float Z = 0.850650808352039932f;
  const float N=0.0f;

  // Uma icoesfera tem 12 vértices e 20 faces. Cada face é um triângulo.
  const float Verts[12][3] ={
      {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
      {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
      {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
  };

  const int Faces[20][4] ={
    {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
    {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
    {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
    {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
  };
};

class Planet {
  std::string name;
  float planetAngle, distanceP;
  glm::vec3 planetLocation;

public:
  void calculateLocation();

};