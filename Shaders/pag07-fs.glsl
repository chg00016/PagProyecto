#version 410

out vec4 colorFragmento;

in salidaVS {
vec3 posicionV;
vec3 normalV;
vec3 colorV;
} entrada;

subroutine vec3 calcularColor();

subroutine (calcularColor) vec3 colorRojo() {
return vec3 (1, 0, 0);
}

subroutine (calcularColor) vec3 colorDifuso() {
return entrada.colorV;
}

subroutine uniform calcularColor seleccionado;

void main() {
colorFragmento = vec4( seleccionado(), 1.0f);
}