#include <iostream>
#include <string>

#include "objmesh.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Planet{
    std::unique_ptr<ObjMesh> planet;
    std::string textureLocation, objectLocation;


public:
    Planet(std::string, std::string);

    void changeTexture( std::string );
    void changeObject( std::string );

    void renderPlanet();
    void loadTexture();

};