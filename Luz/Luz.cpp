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

    void Luz::setID(const glm::vec3& ID) {
        _propiedades._ID = ID;
    }

    void Luz::setIA(const glm::vec3& IA) {
        _propiedades._IA = IA;
    }

    void Luz::setIS(const glm::vec3& IS) {
        _propiedades._IS = IS;
    }

    void Luz::setPosicion(const glm::vec3& pos) {
        _propiedades._p = pos;
    }

    void Luz::setDireccion(const glm::vec3& dir) {
        _propiedades._d = dir;
    }

    void Luz::setGamma(float gamma) {
        _propiedades._gamma = gamma;
    }

    void Luz::setAtenuacion(float s) {
        _propiedades._s = s;
    }

    void Luz::setVision(const glm::mat4& vision) {
        _vision = vision;
    }

    const glm::vec3& Luz::getID() {
        return _propiedades._ID;
    }

    const glm::vec3& Luz::getIA() {
        return _propiedades._IA;
    }

    const glm::vec3& Luz::getIS() {
        return _propiedades._IS;
    }

    const glm::vec3& Luz::getPosicion() {
        return _propiedades._p;
    }

    const glm::vec3& Luz::getDireccion() {
        return _propiedades._d;
    }

    float Luz::getGamma() {
        return _propiedades._gamma;
    }

    float Luz::getAtenuacion() {
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