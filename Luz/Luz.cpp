//
// Created by carme on 01/12/2024.
//

#include "Luz.h"
#include <stdexcept>

namespace PAG {
    Luz::Luz(): _aplicadorSeleccionado(tipoLuzAplicacion::_ninguna), _propiedades() {
        _aplicadores[0] = new LuzPuntualAplicador;
        _aplicadores[1] = new LuzFocalAplicador;
        _aplicadores[2] = new LuzDireccionalAplicador;
        _aplicadores[3] = new LuzAmbienteAplicador;
    }

    void Luz::setLuzAplicador(tipoLuzAplicacion applicatorSelected) {
        _aplicadorSeleccionado = applicatorSelected;
    }

    void Luz::aplicarSubrutina(ShaderPrograms& shaderProgram) {
        if(_aplicadorSeleccionado == tipoLuzAplicacion::_ninguna)
            throw std::runtime_error("[Luz::aplicarLuz]: Tipo de luz sin seleccionar.");

        _aplicadores[_aplicadorSeleccionado]->aplicarSubrutina(shaderProgram);
    }

    void Luz::aplicarLuz(ShaderPrograms& shaderProgram) {
        if(_aplicadorSeleccionado == tipoLuzAplicacion::_ninguna)
            throw std::runtime_error("[Luz::aplicarLuz]: Tipo de luz sin seleccionar.");

        _aplicadores[_aplicadorSeleccionado]->aplicarLuz(_propiedades, _vision, shaderProgram);
    }

    void Luz::setDI(const glm::vec3& DI) {
        _propiedades._dI = DI;
    }

    void Luz::setAI(const glm::vec3& AI) {
        _propiedades._aI = AI;
    }

    void Luz::setSI(const glm::vec3& SI) {
        _propiedades._sI = SI;
    }

    void Luz::setPosition(const glm::vec3& pos) {
        _propiedades._p = pos;
    }

    void Luz::setDirection(const glm::vec3& dir) {
        _propiedades._d = dir;
    }

    void Luz::setGamma(float gamma) {
        _propiedades._gamma = gamma;
    }

    void Luz::setAttenuation(float s) {
        _propiedades._s = s;
    }

    void Luz::setVision(const glm::mat4& vision) {
        _vision = vision;
    }

    const glm::vec3& Luz::getDI() {
        return _propiedades._dI;
    }

    const glm::vec3& Luz::getAI() {
        return _propiedades._aI;
    }

    const glm::vec3& Luz::getSI() {
        return _propiedades._sI;
    }

    const glm::vec3& Luz::getPostition() {
        return _propiedades._p;
    }

    const glm::vec3& Luz::getDirection() {
        return _propiedades._d;
    }

    float Luz::getGamma() {
        return _propiedades._gamma;
    }

    float Luz::getAttenuation() {
        return _propiedades._s;
    }

    const glm::mat4& Luz::getVision() {
        return _vision;
    }


    Luz::~Luz() {
        for(LuzAplicador* aplicador : _aplicadores)
            delete aplicador;
    }
}