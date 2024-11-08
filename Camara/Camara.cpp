//
// Created by carme on 11/10/2024.
//

#include "Camara.h"

namespace PAG {

    Camara::Camara() {
        perspectivaInicial();
        visionInicial();

    }

    const glm::mat4 Camara::TransformacionMVision() const {
        return glm::lookAt(ptoPos, ptoMiraA, vecArriba);
    }


    void Camara::visionInicial() {
        this->angulo = 45.f;
        this->zNear = 1.f;
        this->zFar = 20.f;
        this->aspecto = 4.f / 3.f;
    }


    void Camara::perspectivaInicial() {
        this->ptoPos = glm::vec3(0, 0, 1.5);
        this->ptoMiraA = glm::vec3(0, 0, 0);
        this->vecArriba = glm::normalize(glm::vec3(0, 1, 0));
    }

    const glm::mat4 Camara::TransformacionMProyeccion() const {
        return glm::perspective(glm::radians(angulo), aspecto, zNear, zFar);
    }

    void Camara::pan(float angulo) {
        glm::mat4 transform = glm::translate(ptoPos) *
        glm::rotate(glm::radians(angulo), vecArriba) *
        glm::translate(-ptoPos);

        ptoMiraA = transform * glm::vec4(ptoMiraA, 1.0f);
    }

    void Camara::tilt(float angulo) {
        glm::mat4 transform = glm::translate(ptoPos) *
        glm::rotate(glm::radians(angulo), glm::normalize(glm::cross(vecArriba, ptoPos - ptoMiraA))) *
        glm::translate(-ptoPos);

        ptoMiraA = transform * glm::vec4(ptoMiraA, 1.0f);
        vecArriba = transform * glm::vec4(vecArriba, 0.0f);
    }

    void Camara::dolly(float anguloX, float anguloZ) {
        ptoPos.x   += anguloX;
        ptoMiraA.x += anguloX;

        ptoPos.z   += anguloZ;
        ptoMiraA.z += anguloZ;
    }

    void Camara::crane(float anguloY) {
        ptoPos.y   += anguloY;
        ptoMiraA.y += anguloY;
    }

    void Camara::orbit(float anguloX,  float anguloY) {
        glm::mat4 transform = glm::translate(ptoMiraA) *
        glm::rotate(glm::radians(anguloX), vecArriba) *
        glm::rotate(glm::radians(anguloY), glm::normalize(glm::cross(vecArriba, ptoPos - ptoMiraA))) *
        glm::translate(-ptoMiraA);

        ptoPos = transform * glm::vec4(ptoPos, 1.0f);
        vecArriba = transform * glm::vec4(vecArriba, 1.0f);
    }

    void Camara::zoom(float angulo) {
        this->angulo += angulo;
        if ( this->angulo > 90)
            this->angulo = 90;
        else if ( this->angulo < 0)
            this->angulo = 0;
        TransformacionMProyeccion();
    }

    std::string Camara::switchCamara(PAG::movimientoCamara x) {
        switch (x) {
            case PAN:   return "Pan";
            case TILT:  return "Tilt";
            case DOLLY: return "Dolly";
            case CRANE: return "Crane";
            case ORBIT: return "Orbit";
            case ZOOM:  return "Zoom";
        }
        return "";
    }

    float Camara::getAngulo() {
        return this->angulo;
    }

    void Camara::setAngulo(float angulo) {
        this->angulo = angulo;
    }

    void Camara::setAspecto(float aspecto) {
        this->aspecto = aspecto;
    }

    Camara::~Camara(){}
}
