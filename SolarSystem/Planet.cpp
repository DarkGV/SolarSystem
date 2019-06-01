#include "Planet.hpp"

#include "stb/stb_image.h"
#include "glslprogram.h"

Planet::Planet(std::string objectLocation, std::string textureLocation = "") : infoPlane(10.f, 10.f, 1, 1){
    this->objectLocation = objectLocation;
    this->textureLocation = textureLocation;

    this->planetModel = glm::mat4(1.f);

    if(this->textureLocation.empty() || this->textureLocation == "") throw "Object has no location. Have you set location?";
    planet = ObjMesh::load(this->objectLocation.c_str(), true);
    glGenTextures(1, &textureID);
    data = Texture::loadPixels(this->textureLocation.c_str(), s, t);

    angle = distance_Sun = radius = speed = -1.f;
}

Planet::~Planet(){
    stbi_image_free(data);
    glDeleteTextures(1, &textureID);
}

void Planet::loadTexture(){

    if(this->textureLocation.empty() || this->textureLocation == "") throw "Texture has no location. Have you set location?";

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s, t, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, s, t, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Planet::loadInfoTexture(){
  //if(this->textureLocation.empty() || this->textureLocation == "") throw "Texture has no location. Have you set location?";

  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s_info, t_info, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, s_info, t_info, GL_RGBA, GL_UNSIGNED_BYTE, infoData);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void Planet::loadInfo(std::string infoLocation){
  infoData = Texture::loadPixels(infoLocation.c_str(), s_info, t_info);
}

void Planet::changeTexture (std::string textureLocation){
    this->textureLocation = textureLocation;
}

void Planet::changeObject(std::string objectLocation){
    this->objectLocation = objectLocation;
}

void Planet::renderPlanet(){
    planet->render();
}

void Planet::planetRadius(GLfloat radius){
    this->radius = radius;
}

void Planet::planetAngle(GLfloat angle){
    this->angle = angle;
}

void Planet::planetDistanceSun(GLfloat distance){
    distance_Sun = distance;
}

void Planet::planetSpeed(GLfloat speed){
    this->speed = speed;
}

void Planet::movePlanet(){
    /**
     * Every planet parameter must be defined
     * If there is a planet not defined, it returns an exception
     */
    if(speed == -1 || distance_Sun == -1 || angle == -1 || radius == -1)
        throw "Couldn't calculate planet movement";

    angle += speed;
    while(angle > 360.f)
        angle -= 360.f;

    float temporary_angle = (angle / 180.f) * M_PI;

    this->position = glm::vec3(sin(temporary_angle)* (distance_Sun + 10.f), 0.f, ( cos(temporary_angle) * (distance_Sun + 10.f)) );
    this->planePosition = glm::vec3(sin(temporary_angle)* (distance_Sun+5.f), 0.f, ( cos(temporary_angle) * (distance_Sun+5.f)) );
    planetModel = glm::translate(glm::mat4(1.f), glm::vec3(sin(temporary_angle)*distance_Sun, 0.f, ( cos(temporary_angle) * distance_Sun) ));
}

void Planet::setPlanetOptions(GLfloat radius, GLfloat speed, GLfloat angle, GLfloat distance_Sun){
    this->radius = radius;
    this->angle = angle;
    this->speed = speed;
    this->distance_Sun = distance_Sun;
}

void Planet::lockPlanet(bool locked){
    this->locked = locked;
}

bool Planet::is_locked(){
    return locked;
}
