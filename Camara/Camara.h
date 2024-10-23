//
// Created by carme on 11/10/2024.
//

#ifndef CAMARA_H
#define CAMARA_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <glm/gtc/epsilon.hpp>
namespace PAG {

    enum movimientoCamara{
        PAN, TILT, DOLLY, CRANE, ORBIT, ZOOM
    };

    class Camara {
    private:
        glm::vec3 ptoPos, ptoMiraA, vecArriba;
        float aspecto, zNear, zFar, angulo;

    public:
        Camara();

        const glm::mat4 TransformacionMVision() const;
        const glm::mat4 TransformacionMProyeccion() const;
        void MatrizTranslacion();
        void visionInicial();
        void perspectivaInicial();

        void pan(float angulo);
        void tilt(float angulo);
        void dolly(float anguloX, float diffZ);
        void crane(float anguloY);
        void orbit(float anguloX, float anguloY);
        void zoom(float angulo);
        std::string switchCamara(PAG::movimientoCamara x);
        void setAspecto(float aspecto);
        void setAngulo(float angulo);
        float getAngulo();

        virtual ~Camara();
    };
}

#endif //CAMARA_H
