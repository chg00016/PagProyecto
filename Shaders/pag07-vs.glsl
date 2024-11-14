#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out salidaVS
{
    vec3 posicionV;
    vec3 normalV;
} salida;

void main ()
{//TODO
    salida.posicionV = vec3(view * model * vec4(posicion, 1));
    salida.normalV = vec3(matrizMVit * vec4(normal, 0));
    gl_Position = projection * view * model * vec4 ( posicion, 1 );
    vertexColor = color;
}