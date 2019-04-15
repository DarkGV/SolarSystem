#include "include/Render.hpp"

Render::Render(){
    glewExperimental = true;

    if(glewInit() != GLEW_OK) 
      throw "Couldn't initiate GLEW";
    
    transferData();
}

void Render::transferData(){
  glGenVertexArrays(1, &(this->VertexArrayObject));
  glBindVertexArray(this->VertexArrayObject);
  // Pass Icospheres into VAO
  
  glGenBuffers(1, &this->positionArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, this->positionArrayObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Icosahedron::Verts), Icosahedron::Verts, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &this->facesElementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->facesElementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Icosahedron::Faces), Icosahedron::Faces, GL_STATIC_DRAW);
}

void Render::draw(){
  
}