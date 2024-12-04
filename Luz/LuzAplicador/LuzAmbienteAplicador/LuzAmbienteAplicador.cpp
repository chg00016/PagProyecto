//
// Created by carme on 01/12/2024.
//

#include "LuzAmbienteAplicador.h"

namespace PAG {
    LuzAmbienteAplicador::LuzAmbienteAplicador() : LuzAplicador() {

    }

    LuzAmbienteAplicador::~LuzAmbienteAplicador() {

    }

    void LuzAmbienteAplicador::aplicarSubrutina(ShaderPrograms& shaderProgram) {
        shaderProgram.aplicarSubrutina("ambiente", GL_FRAGMENT_SHADER);
    }

    void LuzAmbienteAplicador::aplicarLuz(PAG::PropiedadesLuz &properties, const glm::mat4& vision, PAG::ShaderPrograms& shaderProgram) {
        shaderProgram.aplicarUniform("Ia", properties._aI);
    }
}