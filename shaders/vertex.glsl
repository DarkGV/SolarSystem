#version 330 core

layout(location = 0) in vec3 planetPosition;
layout(location = 1) in vec3 nothingInteresting;


void main(){
    gl_Position = mat4(1.f) * mat4(1.f) * mat4(1.f) * vec4(planetPosition, 1.f);
}