//
// Created by carme on 01/12/2024.
//

#include "LuzPuntualAplicador.h"
namespace PAG {
    LuzPuntualAplicador::LuzPuntualAplicador(): LuzAplicador(){

    }

    LuzPuntualAplicador::~LuzPuntualAplicador() {

    }

    void LuzPuntualAplicador::aplicarSubrutina(ShaderPrograms& shaderProgram) {
        shaderProgram.aplicarSubrutina("punto", GL_FRAGMENT_SHADER);
    }

    void LuzPuntualAplicador::aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) {
        glm::vec3 pos = glm::vec3(vision * glm::vec4(properties._p, 1.0f));

        shaderProgram.aplicarUniform("posLuz", pos);
        shaderProgram.aplicarUniform("Is", properties._IS);
        shaderProgram.aplicarUniform("Id", properties._ID);
    }
}