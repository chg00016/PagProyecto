#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 color;

uniform mat4 matrizMVP;

out vec3 vertexColor;
void main () {
    gl_Position = matrizMVP * vec4 ( posicion, 1.0 );
    vertexColor = color;
}