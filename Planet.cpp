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

/*#include "include/Planet.hpp"

Planet::Planet(float radius, GLuint nmrSlices, GLuint nmrStacks){
  this->radius = radius;
  this->nmrSlices = nmrSlices;
  this->nmrStacks = nmrStacks;

  float x, y, z, w;
  float length = 1.f/(this->radius);

  float sliceStep = (float)(2 * M_PI / this->nmrSlices);
  float stackStep = (float)(M_PI / this->nmrStacks);
  float sliceAngle, stackAngle;

  for(int i = 0; i <= this->nmrStacks; ++i){
      stackAngle = (float)(M_PI / 2 - i * stackStep);
      w = 1.02f *radius * cosf(stackAngle);
      z = radius * sinf(stackAngle);

      for(int j = 0; j < this->nmrSlices; j++){
          sliceAngle = j*sliceStep;
          x = w * cosf(sliceAngle);
          y = w * sinf(sliceAngle);

          planetVertices.push_back(x);
          planetVertices.push_back(y);
          planetVertices.push_back(z);

          

          planetColor.push_back(1.f);
          planetColor.push_back(0.f);
          planetColor.push_back(0.f);
      }
  }

  for (int i = 0; i <= this->nmrStacks; ++i){
    x = i * (this->nmrSlices + 1);
    y = x + this->nmrSlices +1;

    for (int j = 0; j <= this->nmrSlices; ++j, ++x, ++y){
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

/*Planet::Planet(float radius, GLuint nSlices, GLuint nStacks){
  int nVerts = (nSlices+1) * (nStacks + 1);
    int elements = (nSlices * 2 * (nStacks-1) ) * 3;

    // Verts
    std::vector<GLfloat> p(3 * nVerts);
    // Normals
    std::vector<GLfloat> n(3 * nVerts);
    // Tex coords
    std::vector<GLfloat> tex(2 * nVerts);
    // Elements
    std::vector<GLuint> el(elements);

	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / nSlices;
	GLfloat phiFac = glm::pi<float>() / nStacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for( GLuint i = 0; i <= nSlices; i++ ) {
		theta = i * thetaFac;
                s = (GLfloat)i / nSlices;
		for( GLuint j = 0; j <= nStacks; j++ ) {
			phi = j * phiFac;
                        t = (GLfloat)j / nStacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			p[idx] = (radius * nx)+glm::cos(glm::radians<float>(0.43f)); p[idx+1] = (radius * nx); p[idx+2] = (radius * nx);
			n[idx] = nx; n[idx+1] = ny; n[idx+2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx+1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for( GLuint i = 0; i < nSlices; i++ ) {
		GLuint stackStart = i * (nStacks + 1);
		GLuint nextStackStart = (i+1) * (nStacks+1);
		for( GLuint j = 0; j < nStacks; j++ ) {
			if( j == 0 ) {
				el[idx] = stackStart;
				el[idx+1] = stackStart + 1;
				el[idx+2] = nextStackStart + 1;
				idx += 3;
			} else if( j == nStacks - 1) {
				el[idx] = stackStart + j;
				el[idx+1] = stackStart + j + 1;
				el[idx+2] = nextStackStart + j;
				idx += 3;
			} else {
				el[idx] = stackStart + j;
				el[idx+1] = stackStart + j + 1;
				el[idx+2] = nextStackStart + j + 1;
				el[idx+3] = nextStackStart + j;
				el[idx+4] = stackStart + j;
				el[idx+5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}


}


void Planet::calculateLocation(){
  return;
}*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace GLMAIN {
	GLFWwindow* window;			// Storage For glfw window
    int frameBufferWidth = 800, frameBufferHeight = 800;
	bool paused = false;        // Store whether the animation is paused
	GLuint vao;					// Storage For vao
	// Storage locations of uniforms
	GLint planetLocaionLoc, planetColorLoc, radiusLoc, mvpLoc, mvLoc,
        lightAmbientLoc, reflectAmbientLoc, lightPosLoc;
    GLuint elementBufferHandle;
    int highlightSphere = -1;

	// Store the locations of 6 spheres
	float planetlocations[6][3]=
    {
        {0.0f, 0.0f , 0.0f},
        {0.0f, 6.0f , 0.0f},
        {0.0f, 10.0f , 0.0f},
        {0.0f, 14.0f , 0.0f},
        {0.0f, 18.0f , 0.0f},
        {0.0f, 25.0f , 0.0f}
    };
    // Store the radius of 6 spheres
    float planerRadius[6] = {3.0f, 0.8f, 1.0f, 1.2f, 0.6f, 1.5f};
    // Store the rotate speed of 6 spheres
    float planetSpeed[6] = {3.0f, 2.0f, 2.5f, 1.2f, 1.5f, 1.0f};
    // Store the angles of 6 spheres
    float planetAngle[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    // Store the distances to the star of the 6 spheres
    float planetDistance[6] = {0.0f, 6.0f, 10.0f, 14.0f, 18.0f, 25.0f}; // Planetdistance to the star.
    // Store the base colors  of the 6 spheres
    float planetColor[6][3]=
    {
        {1.0f, 1.0f , 1.0f},
        {1.0f, 1.0f , 0.0f},
        {1.0f, 0.0f , 1.0f},
        {0.0f, 0.0f , 1.0f},
        {0.0f, 1.0f , 0.0f},
        {1.0f, 0.0f , 0.0f}
    };

    // Points and faces of icosphere
    const float X=0.525731112119133606f;
    const float Z=0.850650808352039932f;
    const float N=0.0f;
    const float Verts[12][3]=
    {
        {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
        {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
        {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
    };
    const int Faces[20][3]=
    {
        {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
        {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
        {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
        {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
    };

}

void initPerspective(glm::mat4 & m)
{
    const float aspect = 1;
    const float zNear = 10.0f;
    const float zFar = -1.0f;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = tanf(0.5);
    m[0][0] = 1.0f / (tanHalfFOV * aspect);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHalfFOV;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (zNear + zFar) / (zNear - zFar);
    m[2][3] = 2.0f * zFar * zNear /  (zNear - zFar);
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void updateHighlightSphere()
{
    double x, y;
    glfwGetCursorPos (GLMAIN::window, &x, &y);


    if(x < 0 || y < 0 || x > GLMAIN::frameBufferWidth || y > GLMAIN::frameBufferHeight)
    {
        GLMAIN::highlightSphere = -1;
        return;
    }
    GLubyte pixels[3];

    glReadPixels(x,GLMAIN::frameBufferHeight - y,1,1,GL_RGB,GL_UNSIGNED_BYTE, pixels);

    bool maxFlagPixel[3];
    float pixelRGB[3];
    pixelRGB[0] = pixels[0];
    pixelRGB[1] = pixels[1];
    pixelRGB[2] = pixels[2];

    getMaxFlagfromRGB(maxFlagPixel, pixelRGB);

    int i;
    for(i = 0; i < 6; i ++)
    {
        bool maxFlagSphere[3];
        getMaxFlagfromRGB(maxFlagSphere, GLMAIN::planetColor[i]);
        bool match = true;
        for(int j = 0; j < 3; j ++)
        {
            if(maxFlagSphere[j] != maxFlagPixel[j])  // If any component does not match, check next sphere
            {
                match = false;
                break;
            }
        }
        if(match) // We have found the matched sphere i.
            break;
    }

    GLMAIN::highlightSphere = i; // i is the found sphere, if it is 6, match failed, no object is selected.
    if(i < 6)
        printf("debug: the sphere %d is hovered\n", i);
    return;
}

void calcLocations()
{
    if(GLMAIN::paused)
        return;
    for (int i = 0 ; i < 6; i ++)
    {
        GLMAIN::planetAngle[i] +=  GLMAIN::planetSpeed[i];
        while (GLMAIN::planetAngle[i] > 360.0)
            GLMAIN::planetAngle[i] -= 360.0;
        float tempAngle = (GLMAIN::planetAngle[i] / 180.0) * 3.14159;
        GLMAIN::planetlocations[i][0] = sin(tempAngle) * GLMAIN::planetDistance[i];
        GLMAIN::planetlocations[i][1] = cos(tempAngle) * GLMAIN::planetDistance[i];
    }
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 modelMatrix = glm::mat4(3.0f);
	glm::mat4 mvp = glm::mat4(1.0f);

   	glm::mat4  projectionMatrix;
   	initPerspective(projectionMatrix);


    	// Init view matrix
	const glm::vec3 camPos(-30, 0, 10);// camera position
	const glm::vec3 lookAt(0.0, 0.0, 0.0);
	const glm::vec3 camOffset = lookAt - camPos;
	const glm::vec3 camForward = camOffset /
		glm::length(camOffset);
	const glm::vec3 camUp0(.0f, 0.0f, -1.0f);
	const glm::vec3 camRight = glm::cross(camForward, camUp0);
	const glm::vec3 camUp = glm::cross(camRight, camForward);

	const glm::mat4 viewRotation(
		camRight.x, camUp.x, camForward.
		x, 0.f, // column 0
		camRight.y, camUp.y, camForward.
		y, 0.f, // column 1
		camRight.z, camUp.z, camForward.
		z, 0.f, // column 2
		0.f, 0.f, 0.f, 1.f);// column 3
	const glm::mat4 viewTranslation(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		camPos.x, camPos.y, camPos.z, 1);
	glm::mat4 viewMatrix = viewRotation * viewTranslation;
	glm::mat4 modelViewMareix = viewMatrix * modelMatrix;

	// model -view - projection matrix
	mvp = projectionMatrix * viewMatrix * modelMatrix;


    // Set uniform  mvp
	float mvpFloat[16];
	for (int i = 0; i < 4; i++)
	{
		mvpFloat[i * 4] = mvp[i].x;
		mvpFloat[i * 4 + 1] = mvp[i].y;
		mvpFloat[i * 4 + 2] = mvp[i].z;
		mvpFloat[i * 4 + 3] = mvp[i].w;
	}
	if(GLMAIN::mvpLoc != -1)
		glUniformMatrix4fv(GLMAIN::mvpLoc, 1, false, mvpFloat);

   	 // Set uniform  mv
	float mvFloat[16];
	for (int i = 0; i < 4; i++)
	{
		mvFloat[i * 4] = modelViewMareix[i].x;
		mvFloat[i * 4 + 1] = modelViewMareix[i].y;
		mvFloat[i * 4 + 2] = modelViewMareix[i].z;
		mvFloat[i * 4 + 3] = modelViewMareix[i].w;

	}
   	 if(GLMAIN::mvLoc != -1)
		glUniformMatrix4fv(GLMAIN::mvLoc, 1, false, mvFloat);

	glBindVertexArray(GLMAIN::vao);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    // Draw 6 spheres, the first one is the star
	for(int i = 0; i < 6; i ++)
	{
        glLoadName(i);
        // set planet location
        if(GLMAIN::planetLocaionLoc != -1)
            glUniform3fv(GLMAIN::planetLocaionLoc, 1, &GLMAIN::planetlocations[i][0]);
        // set the raduis of current sphere
        if(GLMAIN::radiusLoc != -1)
            glUniform1f(GLMAIN::radiusLoc, GLMAIN::planerRadius[i]);
        // set color od current sphere
        if(GLMAIN::planetColorLoc != -1)
            glUniform3fv(GLMAIN::planetColorLoc, 1, GLMAIN::planetColor[i]);
        // Set ambient light
        if(GLMAIN::lightAmbientLoc != -1 && GLMAIN::reflectAmbientLoc != -1)
        {
            if(i == 0) // It is the star
            {
                // The star has a bright ambient light.
                float la[3] = {1.0f, 1.0f, 1.0f};
                float ra[3] = {1.0f, 1.0f, 1.0f};
                glUniform3fv(GLMAIN::lightAmbientLoc, 1, la);
                glUniform3fv(GLMAIN::reflectAmbientLoc, 1, ra);
            }
            else if (GLMAIN::highlightSphere == i)
            {
                // The highlighted planet
                float la[3] = {1.0f, 1.0f, 1.0f};
                float ra[3] = {1.0f, 1.0f, 1.0f};
                glUniform3fv(GLMAIN::lightAmbientLoc, 1, la);
                glUniform3fv(GLMAIN::reflectAmbientLoc, 1, ra);

            }
            else
            {
                // The normal planets have normal ambient light.
                float la[3] = {0.8f,0.8f,0.8f};
                float ra[3] = {0.5f,0.5f,0.5f};
                glUniform3fv(GLMAIN::lightAmbientLoc, 1, la);
                glUniform3fv(GLMAIN::reflectAmbientLoc, 1, ra);
            }
        }
        // Set point light
        if(GLMAIN::lightPosLoc != -1)
        {
            float lp[3] = {0.0f,0.0f,0.0f};  // Only have one point light source located at the center of the star(the first sphere).
            glUniform3fv(GLMAIN::lightPosLoc, 1, lp);
        }
        glDrawElements(GL_PATCHES, sizeof(GLMAIN::Faces),  GL_UNSIGNED_INT,  (void*)0 );
	}

    // Update highlight sphere here and in next display the new highlighted sphere could be seen.
    updateHighlightSphere();
	glfwSwapBuffers(GLMAIN::window);
	glfwPollEvents();
}