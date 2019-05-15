#include "Planet.hpp"

#include "stb/stb_image.h"
#include "glslprogram.h"

Planet::Planet(std::string objectLocation, std::string textureLocation = ""){
    this->objectLocation = objectLocation;
    this->textureLocation = textureLocation;
    this->planetModel = glm::mat4(1.f);

    if(this->textureLocation.empty() || this->textureLocation == "") throw "Object has no location. Have you set location?";
    planet = ObjMesh::load(this->objectLocation.c_str(), true);
}

void Planet::loadTexture(){

    if(this->textureLocation.empty() || this->textureLocation == "") throw "Texture has no location. Have you set location?";

    GLint s, t;
    GLubyte *data;

    //glActiveTexture(GL_TEXTURE0);
    data = Texture::loadPixels(this->textureLocation.c_str(), s, t);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s, t, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, s, t, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
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