//
// Created by carme on 01/12/2024.
//

#include "LuzDireccionalAplicador.h"

namespace PAG {
    LuzDireccionalAplicador::LuzDireccionalAplicador(): LuzAplicador() {

    }

    LuzDireccionalAplicador::~LuzDireccionalAplicador() {

    }

    void LuzDireccionalAplicador::aplicarSubrutina(ShaderPrograms& shaderProgram) {
        shaderProgram.aplicarSubrutina("direccional", GL_FRAGMENT_SHADER);
    }

    void LuzDireccionalAplicador::aplicarLuz(PropiedadesLuz &properties, const glm::mat4& vision, ShaderPrograms &shaderProgram) {
        glm::vec3 dir = glm::vec3(vision * glm::vec4(properties._d, 0.0f));

        shaderProgram.aplicarUniform("direccionLuz", dir);
        shaderProgram.aplicarUniform("Is", properties._sI);
        shaderProgram.aplicarUniform("Id", properties._dI);
    }
}