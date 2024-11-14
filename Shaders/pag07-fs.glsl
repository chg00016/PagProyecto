#version 410
out vec4 colorFragmento;

//colores planos
uniform vec4 colorRojo;
//difuso
uniform vec4 Ia;
uniform vec4 Id;
uniform vec4 Is;

uniform vec4 Ka;
uniform vec4 Kd;
uniform vec4 Ks;

in salidaVS
{
    vec3 posicionV;
    vec3 normalV;
} entrada;

subroutine vec4 calcularColor();
subroutine uniform calcularColor metodoColorElegido;

subroutine(calcularColor)
vec4 colorRojo(){ return vec4( 1, 0, 0, 1 );}

subroutine (calcularColor)
vec4 colorVerde(){ return vec4( 0, 1, 0, 1 );}

void main() {
    vec4 color = metodoColorElegido();
}