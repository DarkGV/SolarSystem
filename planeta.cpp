#include <math.h>
#include <iostream>

class Planeta {
  float angp, distSol, raioP, velocidade;
public:
  double posx, posy;
private:
  float tempAngle(){
    return (angp+velocidade)/180 * 3.14159;
  };
public:
  float posxy(){
    float temp = tempAngle();
    posx = sin(temp)*distSol;
    posy = cos(temp)*distSol;
  };
  Planeta(float angp, float distSol, float raioP, float velocidade){
    this->angp = angp;
    this->distSol = distSol;
    this->raioP = raioP;
    this->velocidade = velocidade;
  }
};


int main(){
  Planeta terra(1.85, 10.0, 1.2, 1.2);

  terra.posxy();

  std::cout << terra.posx << " " << terra.posy << std::endl;
}
