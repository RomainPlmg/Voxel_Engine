#version 450 core

layout (location = 0) in vec3 aPos;// The position variable has attribute position 0
layout (location = 1) in vec3 aNormal;// The position variable has attribute position 1
layout (location = 2) in vec3 aColor;// The position variable has attribute position 2

out vec3 vertexColor;
out vec3 normal;
out vec3 fragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    vertexColor = aColor;
    normal = aNormal;
    fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
}