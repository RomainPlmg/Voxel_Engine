#version 450 core

layout (location = 0) in vec3 aPos;// The position variable has attribute position 0
layout (location = 1) in vec3 aColor;// The position variable has attribute position 1

out vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    vertexColor = aColor;
}