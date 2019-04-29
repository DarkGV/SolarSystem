#version 330 core

layout(location = 0) in vec3 planetPosition;

uniform mat4 MVP;
out vec3 vecColor;

void main(){
    gl_Position =  MVP * vec4(planetPosition, 1.f);
    vecColor = vec3(1.f, 0.f, 0.f);
}