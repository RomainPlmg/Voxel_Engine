#version 450 core

out vec4 FragColor;

in vec3 vertexColor;

uniform vec3 ambientLightColor;
uniform float ambiantLightStrength;

void main() {
    vec3 ambiantLight = ambientLightColor * ambiantLightStrength;
    vec3 result = vertexColor * ambiantLight;

    FragColor = vec4(result, 1.0);
}