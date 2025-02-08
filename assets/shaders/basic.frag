#version 450 core

out vec4 FragColor;

in vec3 vertexColor;
in vec3 normal;
in vec3 fragPos;

uniform vec3 ambientLightColor;
uniform float ambiantLightStrength;
uniform vec3 lightPos;

void main() {
    vec3 ambiantLight = ambientLightColor * ambiantLightStrength;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ambientLightColor;

    vec3 result = vertexColor * (ambiantLight + diffuse);

    FragColor = vec4(result, 1.0);
}