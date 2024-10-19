//
// Created by carme on 11/10/2024.
//

#ifndef CAMARA_H
#define CAMARA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace PAG {
    class Camara {
    private:
        glm::vec3 ptoPos, ptoMiraA, vecArriba;
        float aspecto, zNear, zFar, angulo;

    public:
        Camara();

        const glm::mat4& TransformacionMVision() const;
        const glm::mat4& TransformacionMProyeccion() const;
        void MatrizTranslacion();
        void visionInicial();
        void perspectivaInicial();

        void pan(float angulo);
        void tilt(float angulo);
        void dolly(float anguloX, float diffZ);
        void crane(float anguloY);
        void orbit(float anguloX, float anguloY);
        void zoom(float angulo);
        virtual ~Camara();
    };
}

#endif //CAMARA_H
