//
// Created by carme on 01/12/2024.
//

#include "LuzFocalAplicador.h"
namespace PAG {
    LuzFocalAplicador::LuzFocalAplicador(): LuzAplicador() {

    }

    LuzFocalAplicador::~LuzFocalAplicador() {

    }

    void LuzFocalAplicador::aplicarSubrutina(ShaderPrograms& shaderProgram) {
        shaderProgram.aplicarSubrutina("spotlight", GL_FRAGMENT_SHADER);
    }

    void LuzFocalAplicador::aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) {
        glm::vec3 dir = glm::vec3(vision * glm::vec4(properties._d, 0.0f));
        glm::vec3 pos = glm::vec3(vision * glm::vec4(properties._p, 1.0f));

        shaderProgram.aplicarUniform("Id", properties._ID);
        shaderProgram.aplicarUniform("Is", properties._IS);
        shaderProgram.aplicarUniform("posLuz", pos);
        shaderProgram.aplicarUniform("direccionLuz", dir);
        shaderProgram.aplicarUniform("gamma", glm::radians(properties._gamma));
        shaderProgram.aplicarUniform("atenuacion", properties._s);
    }
}