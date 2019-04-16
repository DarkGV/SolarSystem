// #include <math.h>
// #include <iostream>

// class Planeta {
//   float angp, distSol, raioP, velocidade;
// public:
//   double posx, posy;
// private:
//   float tempAngle(){
//     return (angp+velocidade)/180 * 3.14159;
//   };
// public:
//   float posxy(){
//     float temp = tempAngle();
//     posx = sin(temp)*distSol;
//     posy = cos(temp)*distSol;
//   };
//   Planeta(float angp, float distSol, float raioP, float velocidade){
//     this->angp = angp;
//     this->distSol = distSol;
//     this->raioP = raioP;
//     this->velocidade = velocidade;
//   }
// };

#include "include/Planet.hpp"

Planet::Planet(float radius, GLuint nmrSlices, GLuint nmrStacks){
  this->radius = radius;
  this->nmrSlices = nmrSlices;
  this->nmrStacks = nmrStacks;

  float x, y, z, w;
  float length = 1.f/(this->radius);

  float sliceStep = (float)(2 * M_PI / this->nmrSlices);
  float stackStep = (float)(M_PI / this->nmrStacks);
  float sliceAngle, stackAngle;

  for(int i = 0; i < this->nmrStacks; i++){
      stackAngle = (float)(M_PI / 2 - i * stackStep);
      w = 1.02f *radius * cosf(stackAngle);
      z = radius * sinf(stackAngle);

      for(int j = 0; j < this->nmrSlices; j++){
          sliceAngle = j*sliceStep;
          x = w * cosf(sliceAngle);
          z = w * sinf(sliceAngle);

          planetVertices.push_back(x);
          planetVertices.push_back(y);
          planetVertices.push_back(z);

          planetColor.push_back(1.f);
          planetColor.push_back(0.f);
          planetColor.push_back(0.f);
      }
  }

  for (int i = 0; i < this->nmrStacks; i++){
    x = i * (this->nmrSlices + 1);
    y = x + this->nmrSlices +1;

    for (int j = 0; j < this->nmrSlices; j++, ++x, ++y){
      if(i != 0){
        planetIndices.push_back(x);
        planetIndices.push_back(y);
        planetIndices.push_back(x+1);
      }
      if(i != (this->nmrSlices -1)){
        planetIndices.push_back(x+1);
        planetIndices.push_back(y);
        planetIndices.push_back(y+1);
      }
    }
  }
}

void Planet::calculateLocation(){
  return;
}