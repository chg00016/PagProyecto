#version 410
//material
out vec4 fragmentColor;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float brillo;
//luz
uniform vec3 Id;
uniform vec3 Ia;
uniform vec3 Is;
uniform vec3 posLuz;
uniform vec3 direccionLuz;
uniform float gamma;
uniform float atenuacion;

in salidaVS {
    vec3 posicionV;
    vec3 normalV;
    vec3 colorV;
} entrada;

subroutine vec3 calcularColorV();

subroutine (calcularColorV) vec3 spotlight() {
vec3 l = normalize ( posLuz - entrada.posicionV );
vec3 d = normalize ( direccionLuz );
float cosGamma = cos ( gamma );
float dotLD = dot( -l, d );
float spotFactor = pow ( dotLD, atenuacion );

if ( dotLD < cosGamma ) { spotFactor = 0.0f; }

vec3 n = normalize ( entrada.normalV );
vec3 v = normalize ( -entrada.posicionV );
vec3 r = reflect ( -l, n );

vec3 difusa = ( Id * Kd * max( dot( l, n ), 0.0f ) );
vec3 especular = ( Is * Ks * pow ( max( dot( r, v ), 0.0f ), brillo ) );

return spotFactor * ( difusa + especular );
}

subroutine (calcularColorV) vec3 punto() {
vec3 n = normalize ( entrada.normalV );

vec3 l = normalize ( posLuz - entrada.posicionV );
vec3 v = normalize ( -entrada.posicionV );
vec3 r = reflect ( -l, n );

vec3 difusa = ( Id * Kd * max( dot( l, n ), 0.0f ) );
vec3 especular = ( Is * Ks * pow ( max( dot( r, v ), 0.0f ), brillo ) );

return difusa + especular;
}

subroutine (calcularColorV) vec3 direccional() {
vec3 n = normalize ( entrada.normalV );

vec3 l = normalize ( -direccionLuz );
vec3 v = normalize ( -entrada.posicionV );
vec3 r = reflect ( -l, n );

vec3 difusa = ( Id * Kd * max( dot( l, n ), 0.0f ) );
vec3 especular = ( Is * Ks * pow ( max( dot( r, v ), 0.0f ), brillo ) );

return difusa + especular;
}

subroutine (calcularColorV) vec3 ambiente() {
vec3 ambiente = ( Ia * Ka );
return ambiente;
}

subroutine uniform calcularColorV seleccionado;

void main() {
fragmentColor = vec4( seleccionado(), 1.0f);
}