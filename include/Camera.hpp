#pragma once
#include <glm/glm.hpp>

class Camera {
    float posX, posY, posZ, lookX, lookY, lookZ;
public:
    Camera(float posX, float posY, float posZ, float lookX, float lookY, float lookZ){
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;

        this->lookX = lookX;
        this->lookY = lookY;
        this->lookZ = lookZ;
    };

    void updateX(float posX){ this->posX -= posX; };

    void moveForward(float posX, float posY, float posZ){
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;
    };

    void updateLook(float lookX, float lookY, float lookZ){
        this->lookX = lookX;
        this->lookY = lookY;
        this->lookZ = lookZ;
    };

    glm::mat4 updateLookAt(){
        return glm::lookAt(glm::vec3(posX, posY, posZ), glm::vec3(lookX, lookY, lookZ), glm::vec3(0.f, 1.f, 0.f));
    };
};
