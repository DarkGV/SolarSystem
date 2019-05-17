#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 ModelView = view * model;
    TexCoord = VertexTexCoord;
    Normal = normalize( mat3( vec3(ModelView[0]), vec3(ModelView[1]), vec3(ModelView[2]) ) * VertexNormal);
    Position = vec3( ModelView * vec4(VertexPosition,1.0) );

    gl_Position = projection * view * model * vec4(VertexPosition,1.0);
}
