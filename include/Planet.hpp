#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "objmesh.h"
#include "texture.h"
#include "plane.h"

#include <glm/glm.hpp>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

class Planet{
    std::unique_ptr<ObjMesh> planet;
    std::string textureLocation, objectLocation;
    GLuint textureID;
    GLubyte *data, *infoData;
    GLint s, t, s_info, t_info;
    GLfloat angle, radius, speed;
    bool locked = false;

public:
    Plane infoPlane;
    GLfloat distance_Sun;
    glm::mat4 planetModel;
    glm::vec3 position, planePosition;

    /**
     * Constructors and destructors may have be defined
     * There are some heap variables that must be deallocated
     */
    Planet(std::string, std::string);
    ~Planet();

    /**
     * Definition of getters and setters.
     * In this case we just need to set/reset default parameters
     */
    void changeTexture( std::string );
    void changeObject( std::string );
    void planetRadius( GLfloat );
    void planetAngle( GLfloat );
    void planetSpeed ( GLfloat );
    void planetDistanceSun( GLfloat );

    /**
     * Accepts Radius, speed, angle and distance to sun by this order
     */
    void setPlanetOptions( GLfloat, GLfloat, GLfloat, GLfloat );

    /**
     * Define calculations procedures
     * This procesure will use default variable defined in this
     * class for each planet
     */
    void movePlanet();

    /**
     * OpenGL based functions
     */
    void renderPlanet();
    void loadTexture();
    void loadInfo(std::string);
    void loadInfoTexture();

    void lockPlanet(bool);
    bool is_locked();

    //void renderOrbit();

};
